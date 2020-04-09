#include "Parser.hpp"

Parser::Parser(/* args */)
{
}

http::Request* Parser::GetRequest(const string& rawRequest)
{
    stringstream rawRequestStream;
    rawRequestStream << rawRequest;
    http::Request* request = new http::Request();
    string line;

    getline(rawRequestStream, line);
    trim(line);

    request->HttpMethod = GetMethodFromStartLine(line);
    request->RelativeUrl = GetRelativeUrlFromStartLine(line);
    request->QueryParameters = GetQueryParamsFromStartLine(line);

    size_t headerKeyEndPosition;
    string headerKey;
    string headerValue;

    while(getline(rawRequestStream, line))
    {
        trim(line);
        if (line.empty())
            break;

        headerKeyEndPosition = line.find_first_of(':');
        headerKey = line.substr(0, headerKeyEndPosition);
        headerValue = line.substr(headerKeyEndPosition + 2);
        trim(headerValue);

        request->Headers.try_emplace(headerKey, headerValue); 
    };

    string body;
    while(getline(rawRequestStream, line))
    {
        body += line + '\n';
    }
    
    if (body.length() != 0)   
    {        
        body.pop_back();
        request->Body = new char [body.length()+1];
        std::strcpy(request->Body, body.c_str());
    }

    return request;
}

http::Protocol Parser::GetRequestProtocol(const string& rawRequest)
{
    stringstream rawRequestStream;
    rawRequestStream << rawRequest;
    string line;
    getline(rawRequestStream, line);
    trim(line);
    
    auto startPosition = line.find_last_of(' ') + 1;
    string protocol = line.substr(startPosition);
    auto result = http::ProtocolFromString(protocol);

    return result;
}

http::Method Parser::GetMethodFromStartLine(string& line)
{
    auto firstSpacePosition = line.find_first_of(' ');
    string method = line.substr(0, firstSpacePosition);

    return http::MethodFromString(method);
}

string Parser::GetRelativeUrlFromStartLine(string& line)
{
    auto startPosition = line.find_first_of('/') + 1; //TODO: сделать обработку ещё полного адреса и астериска (*)
    auto queryParamsStartPosition = line.find_first_of('?', startPosition);
    auto endPosition = queryParamsStartPosition == line.npos
        ? line.find_first_of(' ', startPosition)
        : queryParamsStartPosition;
    
    return line.substr(startPosition, endPosition - startPosition);
}

unordered_map<string, string> Parser::GetQueryParamsFromStartLine(string& line)
{
    auto lastSpacePosition = line.find_last_of(' ');
    auto queryParamsStartPosition = line.find_first_of('?');
    auto queryParamsString = line.substr(queryParamsStartPosition + 1, lastSpacePosition - queryParamsStartPosition - 1);

    return GetQueryParams(queryParamsString);
}

unordered_map<string, string> Parser::GetQueryParams(string& queryParamsString)
{
    size_t paramsCount = std::count(queryParamsString.begin(), queryParamsString.end(), '=');
    auto nextParamPosition = 0;
    unordered_map<string, string> queryParams;

    for (size_t i = 0; i < paramsCount; i++)
    {
        auto keyEndPosition = queryParamsString.find_first_of('=', nextParamPosition);
        auto key = queryParamsString.substr(nextParamPosition, keyEndPosition - nextParamPosition);

        auto valueEndPosition = queryParamsString.find_first_of('&', nextParamPosition);
        auto value = valueEndPosition == queryParamsString.npos
            ? queryParamsString.substr(keyEndPosition + 1)
            : queryParamsString.substr(keyEndPosition + 1, valueEndPosition - keyEndPosition - 1);

        queryParams.try_emplace(key, value);
        nextParamPosition = valueEndPosition + 1;
    }

    return queryParams;
}

string Parser::GetRawResponse(const http::Response* response, http::Protocol protocol)
{
    stringstream stream;
    string endLine = "\r\n";
    stream << http::ProtocolToString(protocol) \
        << ' ' << response->HttpStatusCode \
        << ' ' << http::StatusCodeToString(response->HttpStatusCode)
        << endLine;

    for (auto &&header : response->Headers)
        stream << header.first << ": " << header.second << endLine;

    stream << endLine;

    if (response->Body)
        stream << response->Body;

    return stream.str();
}


Parser::~Parser()
{
}
