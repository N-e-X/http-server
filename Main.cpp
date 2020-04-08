#include <iostream>
#include "router.hpp"
#include "Server.hpp"
using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
    auto routesMap = GetRoutesMap();
    int port = 5005;
    
    Server(&routesMap).Run(port);

    return 0;
}
