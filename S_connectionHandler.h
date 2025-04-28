#ifndef S_CONNECTIONHANDLER_H
#define S_CONNECTIONHANDLER_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#define BACKLOG 5
#define PORT 65446

class ConnectionHandler {
private:
    WSADATA wsaData;
    SOCKET serverfd, newsocket;
    struct sockaddr_in servaddr; 

public:
    bool setupServer();
    SOCKET getServerFD();
    void cleanup();
};

#endif