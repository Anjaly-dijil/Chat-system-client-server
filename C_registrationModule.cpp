#include "C_registrationModule.h"

RegistrationModule::RegistrationModule(std::string& user,SOCKET clientfd): username(user),clientfd(clientfd){}

bool RegistrationModule::sendRegistration() {
        std::string registerMessage = "SIGNIN:" + username;
        if (send(clientfd, registerMessage.c_str(), registerMessage.length(), 0) < 0) {
            std::cerr << "Failed to send registration message" << "\n";
            return false;
        }

        //std::cout << "Registration message sent with username: " << username << "\n";

        int valread = recv(clientfd, buffer, 1024, 0);
        if(valread > 0){
            std::string response(buffer, valread);
            if (response == "Exists") {
                std::cout << "Username already exists, please try another one." << std::endl;
                return false;
            }
            /*else{
                std::cout <<"List of connected users: " << buffer << std::endl;
            }*/
        }
        else{
            std::cerr<<" Failed to receive list of connected users";
            return false;
        }
        return true;
    }

void RegistrationModule::sendUnregister() {
        std::string unregisterMessage = "SIGNOUT:" + username;
        if(send(clientfd, unregisterMessage.c_str(), unregisterMessage.length(), 0)<0){
            std::cerr<<"Failed to send unregister message"<<std::endl;
        }
        else{
            //std::cout<<"Unregister message sent successfully"<<std::endl;
            exit(0);
        }
    }

void RegistrationModule::chatRequest(std::string& recipient){
        std::string chatrequest = "CHAT:" + recipient;
        if(send(clientfd, chatrequest.c_str(), chatrequest.length(), 0)<0){
            std::cerr<<"Failed to send chat request message"<<std::endl;
        }
        else{
            //std::cout<<"Chat Request sent successfully"<<std::endl;
        }
    }

void RegistrationModule::chatResponse(std::string& response){
        if(send(clientfd, response.c_str(), response.length(), 0)<0){
            std::cerr<<"\nFailed to send chat response"<<std::endl;
        }
        else{
            //std::cout<<"\nChat Response sent successfully"<<std::endl;
        }
    }
