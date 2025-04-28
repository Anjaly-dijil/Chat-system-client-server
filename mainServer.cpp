
#include "S_connectionHandler.h"
#include "S_requestProcessor.h"

#pragma comment(lib, "ws2_32.lib")

#define PORT 65446
#define BACKLOG 5


int main(){
    std::cout<<"-- CHAT SERVICE SYSTEM --";
    ConnectionHandler conhandler;
    if(!conhandler.setupServer()){
        std::cout<<" -- Server side Unsuccessfull---";
        return -1;
    }
    RequestProcessor reqprocessor(conhandler);
    reqprocessor.serverLoop();

    conhandler.cleanup();

    return 0;
}