#include "S_connectionHandler.h"

bool ConnectionHandler::setupServer(){
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "WSAStartup failed" << std::endl;
            return false;
        }
        serverfd = socket(AF_INET,SOCK_STREAM,0);
        if(serverfd == -1){
            std::cerr<<"Socket Creation on Server Side is failed\n";
            WSACleanup();
            return false;
        }
        /*else
            std::cout<<"Socket successfully created on server...\n";*/

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(PORT);

        if((bind(serverfd,(struct sockaddr*)&servaddr,sizeof(servaddr))) < 0){
            std::cerr<<"Error in binding..."<<"\n";
            closesocket(serverfd);
            WSACleanup();
            return false;
        }
        /*else
            std::cout<<"Socket successfully binded...\n";*/

        if(listen(serverfd, BACKLOG) < 0){
            std::cerr<<"Error while listen";
            closesocket(serverfd);
            WSACleanup();
            return false;
        } 
        /*else
            std::cout<<"Server is listening \n";*/

        return true;
    }

SOCKET ConnectionHandler::getServerFD(){
        return serverfd;
    }

void ConnectionHandler::cleanup(){
        closesocket(serverfd);
        WSACleanup();
    }