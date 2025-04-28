#ifndef S_REQUESTPROCESSOR_H
#define S_REQUESTPROCESSOR_H

#include "S_connectionHandler.h"
#include "S_clientRegistry.h"
#include<iostream>
#include<winsock2.h>
#include<ws2tcpip.h>
#include<thread>

class RequestProcessor{
private:
    SOCKET newsocket;
    char buffer[1024] = {0};
    ConnectionHandler& conhandler;
    ClientRegistry clientRegistry;
    std::map<std::string, SOCKET> chatRequests;
    std::mutex chatRequestMutex;

public:
    RequestProcessor(ConnectionHandler& conhandler);
    bool serverLoop();
    void clientThread(SOCKET clientSocket, sockaddr_in clientaddr);
};

#endif