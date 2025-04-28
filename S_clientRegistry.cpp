#include "S_clientRegistry.h"
#include<iostream>


bool ClientRegistry::addClient(const std::string& username, SOCKET clientSocket, const std::string& ipAddress) {
        std::lock_guard<std::mutex> lock(registryMutex);
        if (clientMap.find(username) != clientMap.end()) {
            return false; 
        }
        clientMap[username] = { clientSocket, ipAddress };
        std::cout << "\nClient added: " << username << " (" << ipAddress << ")" << std::endl;
        return true;
    }

void ClientRegistry::removeClient(const std::string& username) {
        std::lock_guard<std::mutex> lock(registryMutex);
        if(clientMap.erase(username)>0){
            std::cout << "\nClient removed: " << username << std::endl;
        }
        else{
            std::cerr<<"\nFailed to remove client:"<<username<<std::endl;
        }
    }

std::string ClientRegistry::getClientList() {
        std::lock_guard<std::mutex> lock(registryMutex);
        std::string clientList = "\n";
        for (const auto& [username, info] : clientMap) {
            clientList += username + " (" + info.ipAddress + ")\n";
        }
        return clientList;
    }

void ClientRegistry::removeClientBySocket(SOCKET clientSocket) {
    std::lock_guard<std::mutex> lock(registryMutex);
    for (auto it = clientMap.begin(); it != clientMap.end(); ++it) {
        if (it->second.socket == clientSocket) {
            std::cout << "Removing client by socket: " << it->first << std::endl;
            clientMap.erase(it);
            return;
        }
    }
    std::cerr << "Client with socket " << clientSocket << " not found." << std::endl;
}

void ClientRegistry::broadcastclientList(const std::string& message){
        std::lock_guard<std::mutex> lock(registryMutex);
        //std::string clientList = getClientList();
        for (auto& [username, clientInfo] : clientMap) {
            send(clientInfo.socket, message.c_str(), message.length(), 0);
        }
}

SOCKET ClientRegistry::getSocketByUserName(const std::string& username){
        std::lock_guard<std::mutex> lock(registryMutex);
        auto it = clientMap.find(username);
        if(it != clientMap.end()){
            return it->second.socket;
        }
        return INVALID_SOCKET;
    }

std::string ClientRegistry::getUserNameBySocket(SOCKET socket){
        std::lock_guard<std::mutex> lock(registryMutex);
        for(const auto& [username,info] : clientMap){
            if(info.socket == socket){
                return username;
            }
        }
        return "";
    }