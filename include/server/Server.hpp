#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "RouteMap.hpp"
#include "HttpHandler.hpp"
#include "ReadWriteHandler.hpp"
#include "Parser.hpp"

typedef struct {
    int Descriptor;
    vector<RouteMap>* RoutesMap;
} ___HandleConnectionArgs;
___HandleConnection(___HandleConnectionArgs* args);

class Server
{
private:
    vector<RouteMap>* _routesMap;
public:
    Server(vector<RouteMap>* routesMap);
    void Run(int port);
    ~Server();
};

#endif