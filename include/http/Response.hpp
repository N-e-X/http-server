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
        StatusCode HttpStatusCode;
        unordered_map<string, string> Headers;
        char* Body;

        /**
         * Response with OK status
         */
        Response() : Response(StatusCode::OK)
        { }
        Response(http::StatusCode statusCode)
        {
            HttpStatusCode = statusCode;
            Headers["Server"] = "PetrSU WebServer-v0.1";
            Body = nullptr;
        }
        Response(http::StatusCode statusCode, const char* body)
        {
            HttpStatusCode = statusCode;
            Headers["Server"] = "PetrSU WebServer-v0.1";
            Headers["Content-Type"] = "text/html; charset=utf-8";
            
            auto bodyLength = strlen(body);
            Headers["Content-Length"] = std::to_string(bodyLength);
            
            Body = new char[bodyLength + 1];
            strcpy(Body, body);
        }
        /**
         * Response with OK status
         */
        Response(const char* body) : Response(StatusCode::OK, body) 
        { }
        Response(http::StatusCode statusCode, unordered_map<string, string> headers)
        {
            HttpStatusCode = statusCode;
            Headers = headers;
            Headers["Server"] = "PetrSU WebServer-v0.1";
            Body = nullptr;
        }
        Response(http::StatusCode statusCode, unordered_map<string, string> headers, const char* body)
        {
            HttpStatusCode = statusCode;
            Headers = headers;
            Headers["Server"] = "PetrSU WebServer-v0.1";
            if (!Headers.count("Content-Type"))
                Headers["Content-Type"] = "text/html; charset=utf-8";

            auto bodyLength = strlen(body);
            Headers["Content-Length"] = std::to_string(bodyLength);
            
            Body = new char[bodyLength + 1];
            strcpy(Body, body);
        }
        ~Response()
        {
            delete[] Body;
        };
    } Response;
}

#endif // RESPONSE_HPP
