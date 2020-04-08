#include "Method.hpp"

namespace http
{
    string MethodToString(Method method)
    {
        switch (method)
        {
        case HEAD: return "HEAD";
        case GET: return "GET";
        case POST: return "POST";
        case PUT: return "PUT";
        case PATCH: return "PATCH";
        case DELETE: return "DELETE";
        case OPTIONS: return "OPTIONS";
        case CONNECT: return "CONNECT";
        case TRACE: return "TRACE";
        
        default: throw MethodToStringConvertionException();
        }
    }

    Method MethodFromString(string str)
    {
        if (str == "HEAD") return HEAD;
        else if (str == "GET") return GET;
        else if (str == "POST") return POST;
        else if (str == "PUT") return PUT;
        else if (str == "PATCH") return PATCH;
        else if (str == "DELETE") return DELETE;
        else if (str == "OPTIONS") return OPTIONS;
        else if (str == "CONNECT") return CONNECT;
        else if (str == "TRACE") return TRACE;

        throw MethodFromStringConvertionException();
    }
}