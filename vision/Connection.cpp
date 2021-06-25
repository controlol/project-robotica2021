#include "Connection.hpp"
#define READ_BUFFER_SIZE 256
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
std::string Connection::ReadData(){
    std::string recvData;
  char buffer[READ_BUFFER_SIZE] = {0}; // create empty buffer to prevent weird data corruption from read
  size_t readBytes = -1;

    
  /*while ((readBytes = read(sockfd, buffer, READ_BUFFER_SIZE))) {
    
    if(readBytes==0) continue;
    if(buffer[0]=='\0')continue;
    std::cout<<"lol"<<buffer<<"lol"<<std::endl;
    recvData.append(buffer);   
    // all data has been read
    if (readBytes < 256 ) break;
  }*/
 //int p = recv(newsockfd,buffer,256,0);
  n = read(newsockfd,buffer,255);
    if (n < 0) 
         std::cout<<("ERROR reading from socket");
    //recvData.append(buffer);
    printf("Here is the message: %s\n",buffer);
    printf("n is: %d\n",n);
    printf("p is: %d\n",errno);
    
  return recvData;
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
