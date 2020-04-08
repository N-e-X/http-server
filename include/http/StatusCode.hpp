#if !defined(HTTP_STATUS_CODE_HPP)
#define HTTP_STATUS_CODE_HPP

#include <string>
#include "StatusCodeToStringConvertionException.hpp"

using std::string;

namespace http {
    /**
     *  Перечисление возможных HTTP-кодов
     **/
    enum StatusCode
    {
        // Informational
        
        Continue = 100,
        SwitchingProtocols = 101,
        Processing = 102,

        // Success

        OK = 200,
        Created = 201,
        Accepted = 202,
        NoContent = 204,

        // Redirection

        MultipleChoices = 300,
        MovedPermamently = 301,
        MovedTemporarily = 302,
        SeeOther = 303,
        NotModified = 304,

        // Client Errors

        BadRequest = 400,
        Unauthorized = 401,
        PaymentRequired = 402,
        Forbidden = 403,
        NotFound = 404,
        MethodNotAllowed = 405,
        RequestTimeout = 408,
        Conflict = 409,
        PayloadTooLarge = 413,
        UriTooLong = 414,

        // Server Errors

        InternalServerError = 500,
        NotImplemented = 501,
        HttpVersionNotSupported = 505
    };

    /**
     * @throw StatusCodeToStringConvertionException
     */
    string StatusCodeToString(StatusCode statusCode);
}

#endif // HTTP_CODE_HPP

