#ifndef C_CONNECTIONMANAGER_H
#define C_CONNECTIONMANAGER_H

#include<iostream>
#include<winsock2.h>
#include<ws2tcpip.h>
#include<string>

#define PORT 65446

class ConnectionManager{
private:
    WSADATA wsaData;
    SOCKET clientfd;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

public:
    bool connectToServer(const std::string& serverIP,int port);
    SOCKET getClientFD();
    void cleanup();
};

#endif