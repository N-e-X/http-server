#if !defined(PARSER_RAW_RESPONSE_TESTS_HPP)
#define PARSER_RAW_RESPONSE_TESTS_HPP

#include <sstream>
#include <cassert>
#include "Parser.hpp"
#include "Response.hpp"

using std::stringstream;
using std::getline;

class ParserRawResponseTests
{
public:
    ParserRawResponseTests(/* args */) { _parser = new Parser(); }
    ~ParserRawResponseTests() { delete _parser; }
    void Run()
    {
        Raw_OK_response_Success();
        Raw_response_with_body_Success();
    }
private:
    Parser* _parser;
    void Raw_OK_response_Success()
    {
        // arrange
        auto response = new http::Response(http::StatusCode::OK);
        auto expectedRawResponse = "\
HTTP/1.0 200 OK\r\n\
Server: PetrSU WebServer-v0.1\r\n\r\n";

        // act
        auto rawResponse = _parser->GetRawResponse(response, http::Protocol::HTTP_1_0);

        // assert
        assert(rawResponse == expectedRawResponse);
    }

    void Raw_response_with_body_Success()
    {
        // arrange
        auto expectedBody = "{\"data\": \"test raw request\"}";
        auto response = new http::Response(http::StatusCode::OK, expectedBody);

        // act
        auto rawResponse = _parser->GetRawResponse(response, http::Protocol::HTTP_1_0);

        // assert
        stringstream stream;
        stream << rawResponse;
        string line;
        string body;
        getline(stream, line);

        while (line != "\r")
            getline(stream, line);

        while (getline(stream, line))
        {
            body.append(line);
        }

        assert(body == expectedBody);
    }
};

#endif // PARSER_RAW_RESPONSE_TESTS_HPP
