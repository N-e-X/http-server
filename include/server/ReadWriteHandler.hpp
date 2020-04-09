#if !defined(READ_WRITE_HANDLER_HPP)
#define READ_WRITE_HANDLER_HPP

#include "IReadWriteHandler.hpp"
#include "RequestTimeoutException.hpp"
#include "ReadSocketException.hpp"
#include <string>
using std::string;

class ReadWriteHandler : public IReadWriteHandler
{
private:
    int _socketDescriptor;
public:
    ReadWriteHandler(int* socketDescriptor);
    /**
     * @throw RequestTimeoutException
     * @throw ReadSocketException
     */
    string ReadRawRequest() override;
    string ReadBytes(int bytesCount) override;
    void WriteRawResponse(const string& rawResponse) override;
    ~ReadWriteHandler() override;
};

#endif // READ_WRITE_HANDLER_HPP
