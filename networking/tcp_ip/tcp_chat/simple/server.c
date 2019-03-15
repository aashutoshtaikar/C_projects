/* Server side C/C++ program to demonstrate Socket programming  
    socket -> bind -> listen -> accept -> r/w
    
    argv[0] = filename 
    argv[1] = port number
 */
#include <stdio.h>  
#include <stdlib.h> 
#include <unistd.h> //for read/write

#include <sys/types.h>
#include <sys/socket.h> 

#include <netinet/in.h> 
#include <string.h> 

void error(const char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) 
{ 
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

	if (argc<2) {
        fprintf(stderr,"port not provided. program terminated\n");
        exit(1);
    }

    //create a socket and have a socket file descriptor   
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd<0) error("error opening the socket\n");

    bzero( (char*)&serv_addr, sizeof(serv_addr)); //clears any data
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    //bind
    if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        error("binding failed");
    }
    
    //listen
    listen(sockfd, 5);

    //accept on a new sock file descriptor 
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr, 
                &clilen);
    if (newsockfd<0) error("error on accept");
    
    
    while(1){
        //read
        bzero(buffer,256); //clear buffer
        n = read(newsockfd,buffer,255);
        if (n<0) error("Error on reading");
        printf("Client: %s\n",buffer);
        
        //write
        bzero(buffer,256); //clear buffer
        printf("Server:");
        fgets(buffer,255,stdin); //reads bytes from stream to buffer
        n = write(newsockfd,buffer,strlen(buffer));
        if (n<0) error("Error on writing");

        int i = strncmp("bye", buffer, 3);
        if (i==0) break;
        
    }

    close(newsockfd);
    close(sockfd);
    return 0;
} 
