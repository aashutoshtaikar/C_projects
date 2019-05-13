#pragma once
#include <stdio.h> //c input output
#include <stdlib.h> //
#include <unistd.h> //for read/write

//system calls
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h> //inet structs like sockaddr_in, functions like socket()
#include <string.h>     //strcpy, strncpy 
#include <pthread.h>    //posix threads

//to reduce code clutter
int guard(int return_value, char * err);


typedef struct Server_manager server_manager;

server_manager* new_server_manager();

//creates a TCP/UDP socket, socket_type=SOCK_STREAM/SOCK_DGRAM
int create_socket(server_manager* server_mgr, int socket_type);
void set_server_address(server_manager* server_mgr, char* argv[]);
void bind_and_listen(server_manager* server_mgr);


void* read_from_client(void* v_newsockfd);
void* shutdown_server(void* tmp);
