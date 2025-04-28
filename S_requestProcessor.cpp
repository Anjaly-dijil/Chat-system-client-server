#include "S_requestProcessor.h"

RequestProcessor::RequestProcessor(ConnectionHandler& conhandler) : conhandler(conhandler){}

bool RequestProcessor::serverLoop(){
        while(true){
            sockaddr_in clientaddr = {};
            int addrlen = sizeof(clientaddr);
            newsocket=accept(conhandler.getServerFD(), (struct sockaddr*)&clientaddr, (socklen_t*)&addrlen);
            if(newsocket < 0){
                std::cerr<<"Error in server accept";
                closesocket(conhandler.getServerFD());
                WSACleanup();
                return false;
            }
            /*else
                std::cout<<"Accept the client";*/

            std::thread(&RequestProcessor::clientThread, this, newsocket, clientaddr).detach();
        }
    }

void RequestProcessor::clientThread(SOCKET clientSocket, sockaddr_in clientaddr){
        const char *msg = " \n*** Welcome to the server! *** ";
        send(clientSocket, msg, strlen(msg), 0);

        while(true){
        int valread = recv(clientSocket, buffer, 1024, 0);
        if(valread > 0){
            buffer[valread] = '\0';
            std::string receivedMsg(buffer);
            std::cout<<"\n";
            std::cout<<receivedMsg;

            if (receivedMsg.find("SIGNIN:") == 0) {
                //std::cout<<"\nRegister the user recieved in server";
                std::string username = receivedMsg.substr(7);
                std::string clientIP = inet_ntoa(clientaddr.sin_addr);
                //std::cout << "\nUsername recieved: " << username << std::endl;

                if(!clientRegistry.addClient(username, clientSocket,clientIP)){
                    std::string errorMsg = "Exists";
                    send(clientSocket, errorMsg.c_str(), errorMsg.length(), 0);
                }
                else{
                    std::string clientList = clientRegistry.getClientList();
                    send(clientSocket, clientList.c_str(), clientList.length(), 0);
                    clientRegistry.broadcastclientList(clientList);
                }
            }

            else if (receivedMsg.find("SIGNOUT:") == 0) {
                //std::cout<<"\nUnregister  message recieved from client";
                std::string username = receivedMsg.substr(8);
                //std::cout<<"\nusername need to remove" << username;
                clientRegistry.removeClient(username);
                closesocket(clientSocket);
                std::string clientList = clientRegistry.getClientList();
                clientRegistry.broadcastclientList(clientList);
                return;
            }

            else if(receivedMsg.find("CHAT:") == 0){
                std::string recipient = receivedMsg.substr(5);

                {   std::lock_guard<std::mutex> lock (chatRequestMutex); 
                    chatRequests[recipient] = clientSocket;
                }

                SOCKET chatSocket  = clientRegistry.getSocketByUserName(recipient);
                if(chatSocket != INVALID_SOCKET){
                    std::string msg = "User wants to chat with you";
                    send(chatSocket, msg.c_str(), msg.length(), 0);
                }
            }
            
            else if(receivedMsg == "ok"){
                std::lock_guard<std::mutex> lock (chatRequestMutex);
                std::string senderUserName = clientRegistry.getUserNameBySocket(clientSocket);
                if(chatRequests.find(senderUserName) != chatRequests.end()){
                    SOCKET senderSocket = chatRequests[senderUserName];
                    std::string response="\nYou can chat now";
                    send(senderSocket,response.c_str(),response.length(),0);
                    chatRequests.erase(senderUserName);
                }
            }
            else if(receivedMsg == "notnow"){
                std::lock_guard<std::mutex> lock (chatRequestMutex);
                std::string senderUserName = clientRegistry.getUserNameBySocket(clientSocket);
                if(chatRequests.find(senderUserName) != chatRequests.end()){
                    SOCKET senderSocket = chatRequests[senderUserName];
                    std::string response="\nYou cannot chat now";
                    send(senderSocket,response.c_str(),response.length(),0);
                    chatRequests.erase(senderUserName);
                }
            }
            
        }
        else{
            std::cerr<<"\nFailed to receive registraion message";
        }
    }

}
