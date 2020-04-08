#include "ParserRequestTests.hpp"
#include "ParserRawResponseTests.hpp"
#include "HttpHandlerTests.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    ParserRequestTests().Run();
    ParserRawResponseTests().Run();
    HttpHandlerTests().Run();

    std::cout << "Tests are passed!" << std::endl;
    return 0;
}