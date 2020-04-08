#if !defined(PROTOCOL_HPP)
#define PROTOCOL_HPP

#include <string>
#include "ProtocolToStringConvertionException.hpp"
#include "ProtocolFromStringConvertionException.hpp"

using std::string;

namespace http
{
    enum Protocol
    {
        HTTP_1_0,
        HTTP_1_1
    };

    /**
     * @throw ProtocolToStringConvertionException
     */
    string ProtocolToString(Protocol protocol);

    /**
     * @throw ProtocolFromStringConvertionException
     */
    Protocol ProtocolFromString(string string);
}

#endif // PROTOCOL_HPP
