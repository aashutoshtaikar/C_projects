/* Server side C/C++ program to demonstrate Socket programming  
    socket -> bind -> listen -> accept -> r/w
    
    argv[0] = filename 
    argv[1] = port number
    reference : http://www.linuxhowtos.org/C_C++/socket.htm
    
    How to kill a process running on particular port(eg. 9003) in Linux? 
    fuser -k 9003/tcp
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //for read/write

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include <netinet/in.h>
#include <string.h>

void error(const char *msg);
int read_from_client(int newsockfd);

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

/*
 There is a separate instance of this function 
 for each connection.  It handles all communication
 once a connnection has been established.
*/
int read_from_client(int newsockfd)
{
    //read
    char buffer[256];
    int n;
    while(1){
        bzero(buffer, 256); //clear buffer
        n = read(newsockfd, buffer, 255);
        if (n < 0)
            error("Error on reading");
        if (strncmp("exit", buffer, 4) == 0) break;

        printf("Client:%d: %s\n",(int)getpid(),buffer);
        
    }
    close(newsockfd);
    return 1;
    
    //write
    // bzero(buffer, 256); //clear buffer
    // printf("Server:");
    // fgets(buffer, 255, stdin); //reads bytes from stream to buffer
    // n = write(newsockfd, buffer, strlen(buffer));
    // if (n < 0)
    //     error("Error on writing");
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd;
    int portno;
    pid_t child_pid, read_pid;

    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 2)
    {
        fprintf(stderr, "port not provided. program terminated\n");
        exit(1);
    }


    //create a socket and have a socket file descriptor
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("error opening the socket\n");

    bzero((char *)&serv_addr, sizeof(serv_addr)); //clears any data
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    //bind
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        error("binding failed");
    }

    //listen can only listen to 5 connections
    listen(sockfd, 5);

    //accept on a new sock file descriptor
    clilen = sizeof(cli_addr);

    while (1)
    {
        // read_pid = fork();
        // if (child_pid < 0) error("error on fork");
        // if (child_pid == 0){
        //     char serv_inp[5];
        //     fgets(serv_inp,sizeof(serv_inp),stdin);
        //     if (strncmp(serv_inp, "exit", 4) == 0 ) {
        //         close(newsockfd);
        //         exit(0);
        //         break;
        //     }
        // } 


        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);  //blocking call
        if (newsockfd < 0)
            error("error on accept");
        child_pid = fork(); //if the accept call succeds create a child proc
        if (child_pid < 0)
            error("error on fork");
        if (child_pid == 0)
        {
            close(sockfd);
            int x = read_from_client(newsockfd);
            if(x==1) break;
            exit(0);
        } 
        // else {
        //     /* in parent */
        //     if (waitpid(child_pid, NULL, 0) < 0) {
        //         perror("Failed to collect child process");
        //         break;
        //     }
        // }
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}
