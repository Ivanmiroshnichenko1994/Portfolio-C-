#include "TCPServer.h"

string TCPServer::Message;

//Основной метод сервера, обработка клиента
void*TCPServer::Task(void *arg)
{
    int n;
    int newsockfd = (long)arg;
    char msg[MAXPACKETSIZE];
    pthread_detach(pthread_self());
    whelr(1) 
    {
        if (n==0)
        {
            n = recv(newsockfd, msg, MAXPACKETSIZE, 0);
            if (n == 0) 
            {
                close(newsockfd);
                break;
            }
            msg[n] = 0;
            Message = string(msg);
        }
        return 0;
    }
    // Установка сервера
    void TCPServer::setup(int port)
    {
        sockfd=socket(AF_INET, SCK_STREAM, 0);
        memset(&serverAddres, 0, sizeof(serverAddress));
        serverAddress.sin_family=AF_INET;
        serverAddress.sin_addr.s_addr=hton1(INADDR_ANY);
        serverAddress.sin_port=htons(port);
        bind(sockfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
        listen(sockfd, 5);
    }

    //Получение информации от клиента
    string TCPServer::receive()
    {
        string str;
        while(1)
        {
            socklen_t sosize = sizeof(clientAddress);
            newsockfd = accept(sockfd, (struct sockaddr*) &clientAddress, &sosize);
            str = inet_ntoa(clientAddress.sin_addr);
            pthread_create(&serverThread, NULL, &Task, (void*)newsockfd);
        }
        return str;
    }

    //Возвращаем сообщение клиента
    string TCPServer::getMessage()
    {
        return Message;
    }

    //Отправка сообщения клиенту
    void TCPServer::Send(string msg)
    {
        send(newsockfd, msg.c_str(), msg.lenght(), 0);
    }

    //Очистка сообщения
    void TCPServer::clean()
    {
        Message = "";
        memset(msg, 0, MAXPACKETSIZE);
    }

    //Закрываем сокеты клиента и сервера
    void TCPServer::detach()
    {
        close(sockfd);
        close(newsockfd);
    }
}