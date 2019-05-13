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

    int accepted_connections;

    struct sockaddr_in server_address, client_address;
    socklen_t clilen;

}server_manager;



server_manager* new_server_manager(){
    server_manager* sm = (server_manager*)malloc(sizeof(sm));
    sm->sockfd = NULL;
    sm->newsockfd = NULL;
    sm->portno = NULL;
    sm->current_state = running;
    sm->clilen = sizeof(sm->client_address);
    return sm;
}


int create_socket(server_manager* sm, int socket_type){
    sm->sockfd = guard(socket(AF_INET, socket_type, 0),"error opening the socket\n");
}

void set_server_address(server_manager* sm, char* argv[]){
    bzero((char*)&sm->server_address);
    sm->portno = atoi(argv[1]);
    sm->server_address.sin_family = AF_INET;
    sm->server_address.sin_addr.s_addr = INADDR_ANY;
    sm->server_address.sin_port = htons(sm->portno);
}

void bind_and_listen(server_manager* sm){
    guard(bind(sm->sockfd, (struct sockaddr *)&sm->server_address, sizeof(sm->server_address)), "binding failed");
    listen(sm->sockfd,5); //5 connections
}

void accept_connections(void* v_sm){
    server_manager* sm = (server_manager*)v_sm;

    pthread_t* thread_pool = NULL;

    while (!sm->current_state)
    {
        sm->newsockfd = guard( accept(sm->sockfd, (struct sockaddr *)(&sm->client_address), &sm->clilen), "error on accept" );
        
        thread_pool=(pthread_t*)realloc(thread_pool,sizeof(*thread_pool)*(sm->accepted_connections+1)); //always realloc with correct ptr cast
        if (thread_pool == NULL){
            printf("thread allocation error: out of memory\n");
            exit(EXIT_FAILURE);
        }
        
        pthread_create(&thread_pool[sm->accepted_connections], NULL, read_from_client, &sm->newsockfd); //create a thread to read      
        sm->accepted_connections++;
    }

    for(int i=0; i<sizeof(thread_pool)/sizeof(*thread_pool);i++){
        free(&thread_pool[i]); 
        thread_pool[i] = NULL;
    }
}

//async detached functions
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