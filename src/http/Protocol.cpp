#include "Protocol.hpp"

namespace http
{
    string ProtocolToString(Protocol protocol)
    {
        switch (protocol)
        {
        case HTTP_1_0: return "HTTP/1.0";
        case HTTP_1_1: return "HTTP/1.1";
        
        default: throw ProtocolToStringConvertionException();
        }
    }

    Protocol ProtocolFromString(string string)
    {
        if (string == "HTTP/1.0") return HTTP_1_0;
        else if (string == "HTTP/1.1") return HTTP_1_1;

        throw ProtocolFromStringConvertionException();
    }
}