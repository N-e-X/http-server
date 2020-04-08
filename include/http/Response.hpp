#if !defined(RESPONSE_HPP)
#define RESPONSE_HPP

#include "StatusCode.hpp"
#include <unordered_map>
#include <cstring>

using std::string;
using std::unordered_map;

namespace http 
{
    typedef struct Response
    {
        StatusCode StatusCode;
        unordered_map<string, string> Headers;
        const char* Body;

        /**
         * Response with OK status
         */
        Response() : Response(StatusCode::OK)
        { }
        Response(http::StatusCode statusCode)
        {
            StatusCode = statusCode;
            Headers["Server"] = "PetrSU WebServer-v0.1";
            Body = nullptr;
        }
        Response(http::StatusCode statusCode, const char* body)
        {
            StatusCode = statusCode;
            Headers["Server"] = "PetrSU WebServer-v0.1";
            Headers["Content-Type"] = "text/html; charset=utf-8";
            Headers["Content-Length"] = std::to_string(strlen(body));
            Body = body;
        }
        /**
         * Response with OK status
         */
        Response(const char* body) : Response(StatusCode::OK, body) 
        { }
        Response(http::StatusCode statusCode, unordered_map<string, string> headers)
        {
            StatusCode = statusCode;
            Headers = headers;
            Headers["Server"] = "PetrSU WebServer-v0.1";
            Body = nullptr;
        }
        Response(http::StatusCode statusCode, unordered_map<string, string> headers, const char* body)
        {
            StatusCode = statusCode;
            Headers = headers;
            Headers["Server"] = "PetrSU WebServer-v0.1";
            if (!Headers.count("Content-Type"))
                Headers["Content-Type"] = "text/html; charset=utf-8";
            Headers["Content-Length"] = std::to_string(strlen(body));
            Body = body;
        }
        ~Response()
        {
            delete Body;
        };
    } Response;
}

#endif // RESPONSE_HPP
