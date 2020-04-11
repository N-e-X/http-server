#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
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
    int recvBytesCount;
    string result;
    bool isHeadersEnd = false;

    recvBytesCount = recv(_socketDescriptor, buffer, bufferSize, 0);
    if(recvBytesCount > 0) //TODO: вынести этот блок в inline-функцию 
    {
        result.append(buffer);
        for (int i = 0; i < recvBytesCount - 3; i++)
        {
            isHeadersEnd = buffer[i] == '\r'
                && buffer[i + 1] == '\n'
                && buffer[i + 2] == '\r'
                && buffer[i + 3] == '\n';
            if (isHeadersEnd)
                break;
        }            
    }

    while (!isHeadersEnd && timeoutSeconds > 0)
    {
        timeoutSeconds--;
        sleep(1);

        recvBytesCount = recv(_socketDescriptor, buffer, bufferSize, MSG_DONTWAIT);
        if(recvBytesCount > 0)
        {
            result.append(buffer);
            for (int i = 0; i < recvBytesCount - 3; i++)
            {
                isHeadersEnd = buffer[i] == '\r'
                    && buffer[i + 1] == '\n'
                    && buffer[i + 2] == '\r'
                    && buffer[i + 3] == '\n';
                if (isHeadersEnd)
                    break;
            }            
        }
    }

    if (result.empty() && timeoutSeconds == 0)
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
    int recvBytesCount;
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
        if (bytesCount <= 0)
            break;

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
    send(_socketDescriptor, rawResponse.c_str(), rawResponse.length(), 0);
}

ReadWriteHandler::~ReadWriteHandler()
{
}
