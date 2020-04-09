#if !defined(REQUEST_HPP)
#define REQUEST_HPP

#include "Method.hpp"
#include <unordered_map>

using std::string;
using std::unordered_map;

namespace http 
{
    typedef struct Request
    {
        string RelativeUrl;
        Method HttpMethod;
        unordered_map<string, string> Headers;
        unordered_map<string, string> QueryParameters;
        char* Body;

        Request() { Body = nullptr; }
        ~Request() { delete[] Body; }
    } Request;
}

#endif // REQUEST_HPP
