#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "RouteMap.hpp"
#include "HttpHandler.hpp"
#include "ReadWriteHandler.hpp"
#include "Parser.hpp"

class Server
{
private:
    vector<RouteMap>* _routesMap;
    void HandleConnection(int* descriptor);
public:
    Server(vector<RouteMap>* routesMap);
    void Run(int port);
    ~Server();
};

#endif