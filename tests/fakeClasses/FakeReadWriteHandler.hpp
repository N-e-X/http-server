#if !defined(FAKE_READ_WRITE_HANDLER)
#define FAKE_READ_WRITE_HANDLER

#include "IReadWriteHandler.hpp"

class FakeReadWriteHandler : public IReadWriteHandler
{
private:
    string _rawRequest;
    string _rawResponse;
public:
    FakeReadWriteHandler(const string rawRequest)
    {
        _rawRequest = rawRequest;
    }
    /**
     * Возвращает сырой запрос и 10 байт тела запроса, если есть
     */
    string ReadRawRequest() override
    {
        auto result = _rawRequest;
        auto bodyStartPosition = _rawRequest.find_last_of("\r\n\r\n") + 1;
        if (bodyStartPosition != _rawRequest.npos)
            result = _rawRequest.substr(0, bodyStartPosition + 10);

        return result;
    }
    /**
     * Возвращает оставшиеся байты тела запроса, если есть
     */
    string ReadBytes(int bytesCount) override
    {
        string result = "";
        auto bodyStartPosition = _rawRequest.find_last_of("\r\n\r\n") + 1;
        if (bodyStartPosition != _rawRequest.npos)
            result = _rawRequest.substr(bodyStartPosition + 10);

        return result;
    }
    void WriteRawResponse(const string& rawResponse) override
    { 
        _rawResponse = rawResponse; 
    }
    string GetRawResponse() 
    { 
        return _rawResponse; 
    }
    ~FakeReadWriteHandler() override
    { }
};

#endif // FAKE_READ_WRITE_HANDLER
