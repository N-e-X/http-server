#include "HttpHandler.hpp"

HttpHandler::HttpHandler(IReadWriteHandler* readWriteHandler, Parser* parser, vector<RouteMap>* routesMap)
{
    _readWriteHandler = readWriteHandler;
    _parser = parser;
    _routesMap = routesMap;
}

void HttpHandler::Handle()
{
    http::Request* request = nullptr;
    http::Response* response = nullptr;

    // протокол ответа по умолчанию, если в запросе не будет другого известного протокола
    http::Protocol protocol = http::Protocol::HTTP_1_1; 

    try
    {
        string rawRequest = _readWriteHandler->ReadRawRequest();
        if (rawRequest.empty())
            throw BadRequestException();

        protocol = _parser->GetRequestProtocol(rawRequest);
        request = _parser->GetRequest(rawRequest);
        ValidateRequest(request, protocol);

        if (request->Headers.count("Content-Length") && request->Body)
        {
            auto missingBytesCount = std::stoi(request->Headers["Content-Length"]) - strlen(request->Body);
            if (missingBytesCount > 0)
            {
                delete request;
                auto missingBody = _readWriteHandler->ReadBytes(missingBytesCount);
                rawRequest.append(missingBody);
                request = _parser->GetRequest(rawRequest);
            }
        }

        response = GetResponse(request);
    }

    catch(const RequestTimeoutException& e) { response = new http::Response(http::StatusCode::RequestTimeout); }
    catch(const MethodFromStringConvertionException& e) { response = new http::Response(http::StatusCode::NotImplemented); }
    catch(const ProtocolFromStringConvertionException& e) { response = new http::Response(http::StatusCode::HttpVersionNotSupported); }
    catch(const BadRequestException& e) { response = new http::Response(http::StatusCode::BadRequest); }
    catch(const std::bad_function_call& e) { std::cerr << e.what() << '\n'; }
    catch(const std::exception& e) { std::cerr << e.what() << '\n'; }
    catch(...) { }

    if (!response)
        response = new http::Response(http::StatusCode::InternalServerError);

    auto rawResponse = _parser->GetRawResponse(response, protocol);

    _readWriteHandler->WriteRawResponse(rawResponse);

    delete request;
    delete response;
}

void HttpHandler::ValidateRequest(const http::Request* request, http::Protocol protocol)
{
    // RFC 2616, section MessageLength 4.4: For compatibility with HTTP/1.0 applications, HTTP/1.1 requests containing a message-body MUST include a valid Content-Length header field unless the server is known to be HTTP/1.1 compliant. If a request contains a message-body and a Content-Length is not given, the server SHOULD respond with 400 (bad request) if it cannot determine the length of the message, or with 411 (length required) if it wishes to insist on receiving a valid Content-Length. 
    
    if (
        (protocol == http::Protocol::HTTP_1_1 && !request->Headers.count("Host"))
        || (request->Body != nullptr && !request->Headers.count("Content-Length"))
        ) //TODO: обработать ситуацию, когда Host не тот
    {
        throw BadRequestException();
    }
}

http::Response* HttpHandler::GetResponse(const http::Request* request)
{
    bool isRouteMatched = false;
    vector<http::Method> allowedMethods;

    for (auto &&routeMap : *_routesMap)
    {
        if (!strcmp(routeMap.Route, request->RelativeUrl.c_str()))
        {
            isRouteMatched = true;
            allowedMethods.push_back(routeMap.HttpMethod);

            if (routeMap.HttpMethod == request->HttpMethod)
                return routeMap.Action(request);
        }
    }

    if (!isRouteMatched)
        return new http::Response(http::StatusCode::NotFound);
    else // совпал маршрут, но не метод
    {
        string allowedMethodsString;

        for (auto &&method : allowedMethods)
        {
            allowedMethodsString.append(http::MethodToString(method));
            allowedMethodsString.append(", ");
        }
        
        if (auto size = allowedMethodsString.size()) // удаляет последнюю ", "
            allowedMethodsString.erase(size - 2, 2);

        return new http::Response(
            http::StatusCode::MethodNotAllowed,
            {{ "Allow", allowedMethodsString }}
        ); 
    }
}

HttpHandler::~HttpHandler()
{
}
