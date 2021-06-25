#include "Connection.hpp"

void Connection::SendData(std::string message)
{
    n = write(newsockfd, message.c_str(), message.size());
    if (n < 0)
        std::cout << ("ERROR writing to socket");
}

bool Connection::WaitForClient()
{
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
                       (struct sockaddr *)&cli_addr,
                       &clilen);
    if (newsockfd < 0)
    {
        std::cout << ("ERROR on accept");
        return false;
    }
    return true;
}

Connection::Connection(int port)
{

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        std::cout << ("ERROR opening socket\n");
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = port;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("[HTTP_SERVER] setsockopt");
        exit(EXIT_FAILURE);
    }
    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
        std::cout << ("ERROR on binding\n");
    listen(sockfd, 5);
}

Connection::~Connection()
{
}
