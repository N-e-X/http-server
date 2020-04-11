#if !defined(HTTP_HANDLER_HPP)
#define HTTP_HANDLER_HPP

#include <cstring>
#include <iostream>
#include "RouteMap.hpp"
#include "IReadWriteHandler.hpp"
#include "Parser.hpp"
#include "RequestTimeoutException.hpp"
#include "BadRequestException.hpp"
#include "MethodFromStringConvertionException.hpp"
#include "ProtocolFromStringConvertionException.hpp"

class HttpHandler
{
private:
    IReadWriteHandler* _readWriteHandler;
    Parser* _parser;
    vector<RouteMap>* _routesMap;
    http::Response* GetResponse(const http::Request* request);
    void ValidateRequest(const http::Request* request, http::Protocol protocol);
public:
    HttpHandler(IReadWriteHandler* readWriteHandler, Parser* parser, vector<RouteMap>* routesMap);
    void Handle();
    ~HttpHandler();
};

#endif // HTTP_HANDLER_HPP
