
#include<thread>

#include "C_connectionManager.h"
#include "C_registrationModule.h"


#pragma comment(lib, "ws2_32.lib")

#define PORT 65446


int main(){
    ConnectionManager cmgr;
    if(!cmgr.connectToServer("127.0.0.1", PORT)){
        std::cout<<" ---Client side UnSuccessfull ---";
        return -1;
    }
    
    std::string username; 
    while(true){
        std::cout<<"\nEnter the username:";
        std::getline(std::cin>>std::ws, username);
        RegistrationModule registration(username,cmgr.getClientFD());
        if(registration.sendRegistration()){
            break;
        }
    }

    std::thread listenThread([&cmgr]() {
        char buffer[1024] = {0};
        while (true) {
            int valread = recv(cmgr.getClientFD(), buffer, 1024, 0);
            if (valread > 0) {
                std::string receivedMsg(buffer, valread);
                std::cout << "\nCurrent Active Users " << receivedMsg << std::endl;
            
                if(receivedMsg.find("User wants to chat with you") != std::string::npos){
                    std::cout<<"\nType 'ok' or 'notnow' ";
                }
        }
      }
    });

    std::cout << "\nType 'exit' to disconnect or \n Type 'chat' to chat\n";
    std::string userInput;
    while (true) {
        std::getline(std::cin >> std::ws, userInput);
        if (userInput == "exit") {
            RegistrationModule registration(username,cmgr.getClientFD());
            registration.sendUnregister();
            break;
        }
        else if(userInput == "chat"){
            std::cout<<"\nEnter recipient's username:";
            std::string recipient;
            std::getline(std::cin>>std::ws, recipient);
            RegistrationModule registration(username,cmgr.getClientFD());
            registration.chatRequest(recipient);
        }
        else  if(userInput == "ok" || userInput == "notnow"){
            RegistrationModule registration(username,cmgr.getClientFD());
            registration.chatResponse(userInput);
        }
        else{
            std::cout<<"\nUnknown command";
        }
    }

    listenThread.join();
    cmgr.cleanup();

    return 0;
}