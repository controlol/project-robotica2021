#ifndef CONNHEADER
#define CONNHEADER

#include<iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<errno.h>

class Connection
{
private:
    int sockfd, newsockfd, portno;
    socklen_t clilen;
   // char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
public:
    Connection(int port);
    bool WaitForClient(); 
    std::string ReadData();
    void SendData(std::string data);
    ~Connection();
};

#endif