#include <sstream>
#include <sys/socket.h>
#include "ReadWriteHandler.hpp"

using std::string;
using std::stringstream;

ReadWriteHandler::ReadWriteHandler(int socketDescriptor)
{
    _socketDescriptor = socketDescriptor;
}

string ReadWriteHandler::ReadRawRequest()
{
    size_t bufferSize = 8192;
    char* buffer = new char[bufferSize] {};
    size_t timeoutSeconds = 15;
    size_t recvBytesCount;
    string result;
    bool isHeadersEnd = false;

    // recvBytesCount = recv(_socketDescriptor, buffer, bufferSize, 0);
    // if ( recvBytesCount < 0 )
    // {
    //     delete[] buffer;
    //     throw ReadSocketException();
    // }

    while (!isHeadersEnd && timeoutSeconds > 0)
    {
        recvBytesCount = recv(_socketDescriptor, buffer, bufferSize, MSG_DONTWAIT);
        if(recvBytesCount > 0)
        {
            result.append(buffer);
            for (size_t i = 0; i < recvBytesCount - 4; i++)
            {
                isHeadersEnd = buffer[i] == '\r'
                    && buffer[i + 1] == '\n'
                    && buffer[i + 2] == '\r'
                    && buffer[i + 3] == '\n';
            }
        }
        timeoutSeconds--;
        sleep(1);
    }

    if (timeoutSeconds == 0)
    {
        delete[] buffer;
        throw RequestTimeoutException();	
    }
    
    delete[] buffer;
    return result;
}

string ReadWriteHandler::ReadBytes(int bytesCount)
{
    size_t bufferSize = 8192;
    char* buffer = new char[bufferSize] {};
    size_t timeoutSeconds = 15;
    size_t recvBytesCount;
    string result;

    while (bytesCount > 0 && timeoutSeconds > 0)
    {
        recvBytesCount = recv(_socketDescriptor, buffer, bufferSize, MSG_DONTWAIT);
        if(recvBytesCount > 0)
        {
            if (recvBytesCount < bytesCount)
                result.append(buffer, recvBytesCount);
            else
                result.append(buffer, bytesCount);
            bytesCount -= recvBytesCount;
        }
        timeoutSeconds--;
        sleep(1);
    }

    if (timeoutSeconds == 0)
    {
        delete[] buffer;
        throw RequestTimeoutException();	
    }
    
    delete[] buffer;
    return result;
}


void ReadWriteHandler::WriteRawResponse(const string& rawResponse)
{
    send(_socketDescriptor, rawResponse, rawResponse.length(), 0); // TODO: проверить, т.к. мб нужно rawResponse.c_str()
}

ReadWriteHandler::~ReadWriteHandler()
{
}
