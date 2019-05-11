#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //for read/write

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

typedef struct server_manager
{
public:
    int sockfd;
    int newsockfd;
    int portno;

    struct sockaddr_in server_address, client_address;
    socklen_t clilen;
};

int create_socket(server_manager* s){

}
