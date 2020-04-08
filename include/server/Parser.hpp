#if !defined(PARSER_HPP)
#define PARSER_HPP

#include "string_utils.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Method.hpp"
#include "Protocol.hpp"
#include <unordered_map>
#include <cstring>
#include <sstream>

using std::string;
using std::stringstream;
using std::unordered_map;
using std::getline;

class Parser
{
private:
    // Request private methods
    http::Method GetMethodFromStartLine(string& line);
    string GetRelativeUrlFromStartLine(string& line);
    unordered_map<string, string> GetQueryParamsFromStartLine(string& line);
    unordered_map<string, string> GetQueryParams(string& queryParamsString);
    // Response private methods
    

public:
    Parser(/* args */);
    /**
     * Получить объект запроса из потока сырых данных
     * @throw MethodFromStringConvertionException
     */
    http::Request* GetRequest(const string& rawRequest);
    /**
     * Получить протокол запроса
     * @throw ProtocolFromStringConvertionException
     */
    http::Protocol GetRequestProtocol(const string& rawRequest);
    /**
     * Получить поток сырых данных ответа из объекта ответа
     * @protocol - протокол, с которым будет сформирован ответ
     * @throw StatusCodeToStringConvertionException
     */
    string GetRawResponse(const http::Response* response, http::Protocol protocol);
    ~Parser();
};

#endif // PARSER_HPP
