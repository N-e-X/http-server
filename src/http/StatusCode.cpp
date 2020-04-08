#include "StatusCode.hpp"

namespace http 
{
    string StatusCodeToString(StatusCode statusCode)
    {
        switch (statusCode)
        {
        case Continue: return "Continue";
        case SwitchingProtocols: return "Switching Protocols";
        case Processing: return "Processing";

        case OK: return "OK";
        case Created: return "Created";
        case Accepted: return "Accepted";
        case NoContent: return "No Content";

        case MultipleChoices: return "Multiple Choices";
        case MovedPermamently: return "Moved Permamently";
        case MovedTemporarily: return "Moved Temporarily";
        case SeeOther: return "See Other";
        case NotModified: return "Not Modified";

        case BadRequest: return "Bad Request";
        case Unauthorized: return "Unauthorized";
        case PaymentRequired: return "Payment Required";
        case Forbidden: return "Forbidden";
        case NotFound: return "Not Found";
        case MethodNotAllowed: return "Method Not Allowed";
        case RequestTimeout: return "Request Timeout";
        case Conflict: return "Conflict";
        case PayloadTooLarge: return "Payload Too Large";
        case UriTooLong: return "Uri Too Long";

        case InternalServerError: return "Internal Server Error";
        case NotImplemented: return "Not Implemented";
        case HttpVersionNotSupported: return "Http Version Not Supported";

        default: throw StatusCodeToStringConvertionException();
        }
    }
}