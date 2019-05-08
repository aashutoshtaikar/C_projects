/* Server side C/C++ program to demonstrate Socket programming  
    socket -> bind -> listen -> accept -> r/w
    
    argv[0] = filename 
    argv[1] = port number
    references : 
    1. http://www.linuxhowtos.org/C_C++/socket.htm
    2. https://stackoverflow.com/questions/11160763/create-a-dynamic-number-of-threads
    3. https://jameshfisher.com/2017/02/28/tcp-server-pthreads.html // good way of using guard statements to reduce code clutter
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //for read/write

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

//forward decls

int guard(int return_value, char * err);
void* read_from_client(void* v_newsockfd);
void* shutdown_server(void* tmp);

//to reduce code clutter
int guard(int return_value, char * err) {
    if (return_value == -1){ 
        perror(err); 
        exit(1); 
    } 
    return return_value; 
}

//reads from clients over newsockfd passed via each thread
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

//daemon shuts down the server on reading exit from stdin
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

int main(int argc, char *argv[]){
    
    if (argc < 2){
        fprintf(stderr, "port not provided. program terminated\n");
        exit(1);
    }

    int sockfd; 
    int newsockfd; 
    int portno;
 
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    pthread_t* thread_pool;
    pthread_t exit_thread;

    //create a socket and have a socket file descriptor
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("error opening the socket\n");

    //init serv_addr
    bzero((char *)&serv_addr, sizeof(serv_addr)); 
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    //bind & listen
    guard( bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)), "binding failed");
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    
    thread_pool = (pthread_t*)malloc(sizeof(*thread_pool) * 1); //sizeof(pthread_t) is fine but with sizeof(*thread_pool) its stays type safe
    int accepted_conn_num = 0;  // index for accessing thread pool
    
    int state = 0;
    pthread_create(&exit_thread, NULL, shutdown_server, &state);
    
    while (!state)
    {
        newsockfd = guard( accept(sockfd, (struct sockaddr *)&cli_addr, &clilen), "error on accept" );
        
        thread_pool=(pthread_t*)realloc(thread_pool,sizeof(*thread_pool)*(accepted_conn_num+1)); //always realloc with correct ptr cast
        if (thread_pool == NULL){
            printf("out of memory\n");
            exit(EXIT_FAILURE);
        }
        
        pthread_create(&thread_pool[accepted_conn_num], NULL, read_from_client, &newsockfd); //create a thread to read
       
        accepted_conn_num++;
    }
    free(thread_pool); // need to do a lot more than this to avoid memory leaks
    
    close(sockfd);
    return 0;
}

/* scratch code */
    ////write scope:read_from_client(...)
    // bzero(buffer, 256); //clear buffer
    // printf("Server:");
    // fgets(buffer, 255, stdin); //reads bytes from stream to buffer
    // n = write(newsockfd, buffer, strlen(buffer));
    // if (n < 0)
    //     error("Error on writing");

    ////scope: pthread_create(thread_pool...)
    //pthread_join(thread_pool[accepted_conn_num], NULL); //can't do this, it blocks other clients

    //need improvements to get rid of the while loop