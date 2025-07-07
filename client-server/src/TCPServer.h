#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <vector>
#include <pthread.h>

using namespace std;
#define MAXPOCKETSIZE 4096;
class TCPServer
{
    public:
    int sockfd, newsockfd, n, pid;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    pthread_t serverThread;
    char msg[MAXPACKETSIZE];
    static string Meessage;

    void setup(int port);
    string receive();
    string getMessage();
    void Send(string msg);
    void detach();
    void clean();

    private:
    static void *Task(void *argv);
};

#endif