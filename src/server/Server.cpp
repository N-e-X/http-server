#include "Server.hpp"

Server::Server(vector<RouteMap>* routesMap)
{
    _routesMap = routesMap;
}

void Server::Run(int port)
{
    struct sockaddr_in socket_address;
    pthread_t thread;

    signal(SIGPIPE, SIG_IGN); // игнорируем сигнал обрыва соединения

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Невозможно открыть сокет!" << std::endl;
        return;
    }

    int option_value = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(int));

    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port);
    socket_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr *) &socket_address, sizeof(socket_address)) == -1) {
        close(sock);
        std::cerr << "Указанный порт занят!" << std::endl;
        return;
    }

    listen(sock, SOMAXCONN);
    std::cout << "Сервер запущен. Порт: " << port << std::endl\
        << "Ожидание подключений..." << std::endl;
    while (1) {
        int *descriptor = (int*)malloc(sizeof(int));		
        *descriptor = accept(sock, NULL, NULL); // Ожидание нового подключения
        pthread_create(&thread, NULL, (void*)&HandleConnection, descriptor); // Запуск задачи в новом потоке
    }
    pclose(sock);
}

void Server::HandleConnection(int* descriptor)
{
    auto readWriteHandler = new ReadWriteHandler(descriptor);
    auto parser = new Parser();
    auto httpHandler = new HttpHandler(readWriteHandler, parser, _routesMap);

    httpHandler->Handle();

    delete httpHandler;
    delete parser;
    delete readWriteHandler;

    pclose(descriptor);
    pthread_exit(0);
}

Server::~Server()
{
}

