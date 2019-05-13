#pragma once
#include"server_manager.h"

int guard(int return_value, char* err)
{
    if (return_value == -1){ 
        perror(err); 
        exit(1); 
    } 
    return return_value; 
}

enum server_states{running, shutdown};

typedef struct Server_manager
{
    int sockfd;
    int newsockfd;
    int portno;
    enum server_states current_state;

    struct sockaddr_in server_address, client_address;
    socklen_t clilen;

}server_manager;



server_manager* new_server_manager(){
    server_manager* server_mgr = (server_manager*)malloc(sizeof(server_mgr));
    server_mgr->sockfd = NULL;
    server_mgr->newsockfd = NULL;
    server_mgr->portno = NULL;
    server_mgr->current_state = running;
    server_mgr->clilen = sizeof(server_mgr->client_address);
    return server_mgr;
}


int create_socket(server_manager* server_mgr, int socket_type){
    server_mgr->sockfd = guard(socket(AF_INET, socket_type, 0),"error opening the socket\n");
}

void set_server_address(server_manager* server_mgr, char* argv[]){
    bzero((char*)&server_mgr->server_address);
    server_mgr->portno = atoi(argv[1]);
    server_mgr->server_address.sin_family = AF_INET;
    server_mgr->server_address.sin_addr.s_addr = INADDR_ANY;
    server_mgr->server_address.sin_port = htons(server_mgr->portno);
}

void bind_and_listen(server_manager* server_mgr){
    guard(bind(server_mgr->sockfd, (struct sockaddr *)&server_mgr->server_address, sizeof(server_mgr->server_address)), "binding failed");
    listen(server_mgr->sockfd,5); //5 connections
}

void* read_from_client(void* v_newsockfd)
{
    pthread_detach(pthread_self());
    int newsockfd = *((int*) v_newsockfd);
    char buffer[256];
    int n;
    while(1){
        bzero(buffer, 256); //clear buffer
        guard(read(newsockfd, buffer, 255), "Error on reading");
        if ((strncmp("exit", buffer, 4) == 0) || (strcmp("", buffer) == 0)) break;
        printf("Client:%d: %s\n",(int)(pthread_self()),buffer);
    }
    close(newsockfd);
}

void* shutdown_server(void* tmp)
{    
    pthread_detach(pthread_self());
    char input[5];
    fgets(input,5,stdin);
    
    if (strncmp(input,"exit",4)==0) {
        printf("Shutting down server...\n");
        *((int*)tmp) = 1; //exit(EXIT_FAILURE); //can't do this need to free resources
    }  
}