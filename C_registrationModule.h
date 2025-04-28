#ifndef C_REGISTRATIONMODULE_H
#define C_REGISTRATIONMODULE_H

#include<iostream>
#include<winsock2.h>
#include<ws2tcpip.h>
#include<string>

class RegistrationModule{
private:
    std::string username;
    SOCKET clientfd;
    char buffer[1024] = {0};

public:
    RegistrationModule(std::string& user,SOCKET clientfd);
    bool sendRegistration();
    void sendUnregister();
    void chatRequest(std::string& recipient);
    void chatResponse(std::string& response);
};

#endif