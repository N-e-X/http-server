#if !defined(PARSER_REQUEST_TESTS_HPP)
#define PARSER_REQUEST_TESTS_HPP

#include <cassert>
#include "Parser.hpp"

class ParserRequestTests
{
public:
    ParserRequestTests() { _parser = new Parser(); }
    ~ParserRequestTests() { delete _parser; }
    void Run()
    {
        Method_head_Success();
        Method_get_Success();
        Method_post_Success();
        Protocol_http_1_0_Success();
        Protocol_http_1_1_Success();
        Without_query_params_Success();
        Query_params_Success();
        Headers_Success();
        Body_Success();
    }

private:
    Parser* _parser;
    void Method_head_Success()
    {
        // arrange
        auto rawRequest = "HEAD / HTTP/1.0\r\n\r\n";
        // act
        auto request = _parser->GetRequest(rawRequest);
        // assert
        assert(request->HttpMethod == http::Method::HEAD);

        delete request;
    }

    void Method_get_Success()
    {
        // arrange
        auto rawRequest = "GET / HTTP/1.0\r\n\r\n";
        // act
        auto request = _parser->GetRequest(rawRequest);
        // assert
        assert(request->HttpMethod == http::Method::GET);

        delete request;
    }

    void Method_post_Success()
    {
        // arrange
        auto rawRequest = "POST / HTTP/1.0\r\n\r\n";
        // act
        auto request = _parser->GetRequest(rawRequest);
        // assert
        assert(request->HttpMethod == http::Method::POST);

        delete request;
    }

    void Protocol_http_1_0_Success()
    {
        // arrange
        auto rawRequest = "HEAD / HTTP/1.0\r\n\r\n";
        // act
        auto protocol = _parser->GetRequestProtocol(rawRequest);
        // assert
        assert(protocol == http::Protocol::HTTP_1_0);
    }

    void Protocol_http_1_1_Success()
    {
        // arrange
        auto rawRequest = "HEAD / HTTP/1.1\r\n\r\n";
        // act
        auto protocol = _parser->GetRequestProtocol(rawRequest);
        // assert
        assert(protocol == http::Protocol::HTTP_1_1);
    }

    void Without_query_params_Success()
    {
        // arrange
        auto rawRequest = "HEAD / HTTP/1.0\r\n\r\n";
        // act
        auto request = _parser->GetRequest(rawRequest);
        // assert
        assert(request->QueryParameters.empty());
        assert(request->RelativeUrl == "");

        delete request;
    }

    void Query_params_Success()
    {
        // arrange
        auto rawRequest = "HEAD /index?a=true&b=1 HTTP/1.0\r\n\r\n";
        // act
        auto request = _parser->GetRequest(rawRequest);
        // assert
        assert(request->QueryParameters["a"] == "true");
        assert(request->QueryParameters["b"] == "1");
        assert(request->RelativeUrl == "index");

        delete request;
    }

    void Headers_Success()
    {
        // arrange GET / HTTP/1.1\r\nHost: alizar.habrahabr.ru\r\n\r\n
        auto rawRequest = "\
        GET / HTTP/1.1\r\n\
        Host: localhost\r\n\
        Connection: close\r\n\r\n\
        ";
        // act
        auto request = _parser->GetRequest(rawRequest);
        // assert
        assert(request->Headers["Host"] == "localhost");
        assert(request->Headers["Connection"] == "close");
        delete request;
    }

    void Body_Success()
    {
        // arrange
        string rawRequest = "\
        POST / HTTP/1.1\r\n\
        Host: localhost\r\n\
        Connection: close\r\n\r\n";

        string body = "\
        {\
            \"id\": \"1\",\
            \"name\": \"Artyom\",\
        }";

        rawRequest.append(body);
        // act
        auto request = _parser->GetRequest(rawRequest);
        // assert
        assert(request->Body != nullptr);
        assert(string(request->Body) == body);
        delete request;
    }
};

#endif // PARSER_REQUEST_TESTS_HPP