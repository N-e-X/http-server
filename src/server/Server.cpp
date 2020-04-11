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
        auto args = new ___HandleConnectionArgs();
        args->RoutesMap = _routesMap;
        args->Descriptor = accept(sock, NULL, NULL); // Ожидание нового подключения

        pthread_create(&thread, NULL, (void*)___HandleConnection, args); // Запуск задачи в новом потоке
    }
    close(sock);
}

void* ___HandleConnection(___HandleConnectionArgs* args)
{
    auto readWriteHandler = new ReadWriteHandler(args->Descriptor);
    auto parser = new Parser();
    auto httpHandler = new HttpHandler(readWriteHandler, parser, args->RoutesMap);

    httpHandler->Handle();

    delete httpHandler;
    delete parser;
    delete readWriteHandler;

    close(args->Descriptor);
    delete args;
    pthread_exit(0);
}

Server::~Server()
{
}

