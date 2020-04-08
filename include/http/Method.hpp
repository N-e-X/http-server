#if !defined(HTTP_METHOD_HPP)
#define HTTP_METHOD_HPP

#include "MethodFromStringConvertionException.hpp"
#include "MethodToStringConvertionException.hpp"
#include <string>

using std::string;

namespace http {
    /**
     *  Перечисление возможных HTTP-методов
     **/
    enum Method 
    {
        HEAD,
        GET,
        POST,
        PUT,
        PATCH,
        DELETE,
        OPTIONS,
        CONNECT,
        TRACE
    };

    /**
     * @throw MethodToStringConvertionException
     */
    string MethodToString(Method method);

    /**
     * @throw MethodFromStringConvertionException
     */
    Method MethodFromString(string str);
}

#endif // HTTP_METHOD_HPP

