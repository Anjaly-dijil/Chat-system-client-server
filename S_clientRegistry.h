#ifndef S_CLIENTREHISTRY_H
#define S_CLIENTREHISTRY_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include<mutex>
#include<map>
#include<string>

class ClientRegistry {
private:
    struct ClientInfo {
        SOCKET socket;
        std::string ipAddress;
    };

    std::map<std::string, ClientInfo> clientMap;  // Maps username to ClientInfo
    std::mutex registryMutex;  // Protects access to clientMap

public:
    bool addClient(const std::string& username, SOCKET clientSocket, const std::string& ipAddress);
    void removeClient(const std::string& username);
    std::string getClientList();
    void broadcastclientList(const std::string& message);
    void removeClientBySocket(SOCKET clientSocket);
    SOCKET getSocketByUserName(const std::string& username);
    std::string getUserNameBySocket(SOCKET socket);
};

#endif