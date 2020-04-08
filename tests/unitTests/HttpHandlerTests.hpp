#if !defined(RESPONSE_HANDLER_TESTS_HPP)
#define RESPONSE_HANDLER_TESTS_HPP

#include <cassert>
#include "HttpHandler.hpp"
#include "FakeReadWriteHandler.hpp"
#include "RouteMap.hpp"

class HttpHandlerTests
{
public:
    HttpHandlerTests(/* args */) 
    {
        _parser = new Parser();
        _routesMap = 
        {
            RouteMap(
                "", 
                http::Method::HEAD, 
                [](const http::Request* request) { return new http::Response();}
            ),
            RouteMap(
                "body", 
                http::Method::POST, 
                [](const http::Request* request) { return new http::Response();}
            ),
            RouteMap(
                "newPage", 
                http::Method::GET, 
                [](const http::Request* request) { return new http::Response(); }
            )
        };
    }
    ~HttpHandlerTests() { delete _parser; }
    void Run()
    {
        Handle_request_Success();
        Handle_request_with_short_body_Success();
        Handle_request_with_long_body_Success();
        Handle_request_of_wrong_method_to_the_entity_Returns_405_method_not_allowed();
    }
private:
    Parser* _parser;
    vector<RouteMap> _routesMap;
    void Handle_request_Success()
    {
        // arrange
        auto rawRequest = "HEAD / HTTP/1.0\r\n\r\n";
        auto expectedRawResponse = "\
HTTP/1.0 200 OK\r\n\
Server: PetrSU WebServer-v0.1\r\n\r\n";

        auto readWriteHandler = new FakeReadWriteHandler(rawRequest);
        auto httpHandler = new HttpHandler(readWriteHandler, _parser, &_routesMap);
        
        // act
        httpHandler->Handle();
        
        // assert
        auto rawResponse = readWriteHandler->GetRawResponse();
        assert(rawResponse == expectedRawResponse);

        delete readWriteHandler;
        delete httpHandler;
    }

    void Handle_request_with_short_body_Success()
    {
        // arrange
        auto rawRequest = "\
POST /body HTTP/1.0\r\n\
Content-Length: 5\r\n\
Content-Type: text/html; charset=utf-8\r\n\
\r\n\
hello";
        auto expectedRawResponse = "\
HTTP/1.0 200 OK\r\n\
Server: PetrSU WebServer-v0.1\r\n\r\n";

        auto readWriteHandler = new FakeReadWriteHandler(rawRequest);
        auto httpHandler = new HttpHandler(readWriteHandler, _parser, &_routesMap);
        
        // act
        httpHandler->Handle();
        
        // assert
        auto rawResponse = readWriteHandler->GetRawResponse();
        assert(rawResponse == expectedRawResponse);

        delete readWriteHandler;
        delete httpHandler;
    }

        void Handle_request_with_long_body_Success()
    {
        // arrange
        auto rawRequest = "\
POST /body HTTP/1.0\r\n\
Content-Length: 17\r\n\
Content-Type: text/html; charset=utf-8\r\n\
\r\n\
hello hello hello";
        auto expectedRawResponse = "\
HTTP/1.0 200 OK\r\n\
Server: PetrSU WebServer-v0.1\r\n\r\n";

        auto readWriteHandler = new FakeReadWriteHandler(rawRequest);
        auto httpHandler = new HttpHandler(readWriteHandler, _parser, &_routesMap);
        
        // act
        httpHandler->Handle();
        
        // assert
        auto rawResponse = readWriteHandler->GetRawResponse();
        assert(rawResponse == expectedRawResponse);

        delete readWriteHandler;
        delete httpHandler;
    }

    void Handle_request_of_wrong_method_to_the_entity_Returns_405_method_not_allowed()
    {
        // arrange
        auto rawRequest = "POST / HTTP/1.0\r\n\r\n";
        auto expectedRawResponse = "\
HTTP/1.0 405 Method Not Allowed\r\n\
Server: PetrSU WebServer-v0.1\r\n\
Allow: HEAD\r\n\r\n";

        auto readWriteHandler = new FakeReadWriteHandler(rawRequest);
        auto httpHandler = new HttpHandler(readWriteHandler, _parser, &_routesMap);
        
        // act
        httpHandler->Handle();
        
        // assert
        auto rawResponse = readWriteHandler->GetRawResponse();
        assert(rawResponse == expectedRawResponse);

        delete readWriteHandler;
        delete httpHandler;
    }
};

#endif // RESPONSE_HANDLER_TESTS_HPP
