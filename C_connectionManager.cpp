#include "C_connectionManager.h"
#include<iostream>
#include<thread>

bool ConnectionManager::connectToServer(const std::string& serverIP,int port){
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "WSAStartup failed" << "\n";
            return false;
        }

        if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            std::cerr << "Socket creation error" << "\n";
            WSACleanup();
            return false;
        }
        /*else
            printf("Socket successfully created..\n");*/

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(serverIP.c_str());
        serv_addr.sin_port = htons(port);

        if(connect(clientfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
            std::cerr << "Connection with the server failed" << "\n";
            closesocket(clientfd);
            WSACleanup();
            return false;
        }
        /*else
            std::cout << "Connected to the server" << "\n";*/

        int valread = recv(clientfd, buffer, 1024, 0);
        if(valread > 0){
            std::cout << "Server: " << buffer << std::endl;
        }
        else{
            std::cerr<<" Failed to receive message";
        }
        return true;
    }

SOCKET ConnectionManager::getClientFD(){
        return clientfd;
    }

void ConnectionManager::cleanup(){
        closesocket(clientfd);
        WSACleanup();
    }
    