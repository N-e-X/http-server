#if !defined(IREAD_WRITE_HANDLER_HPP)
#define IREAD_WRITE_HANDLER_HPP

#include <string>
using std::string;

class IReadWriteHandler {
public:
    virtual string ReadRawRequest() = 0;
    virtual string ReadBytes(int bytesCount) = 0;
    virtual void WriteRawResponse(const string& rawResponse) = 0;
    virtual ~IReadWriteHandler() {}; // destructor, use it to call destructor of the inherit classes
};

#endif // IREAD_WRITE_HANDLER_HPP
