/* Client side C/C++ program to demonstrate Socket programming
    socket -> connect -> writes to server
    
    argv[0] = filename 
    argv[1] = server address
    argv[2] = port no
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> //for read/write

#include <sys/types.h>
#include <sys/socket.h> 

#include <netinet/in.h> 
#include <netdb.h> // defines the hostent structure which has host name and ipv4 address
#include <string.h> 

int guard(int return_value, char * err) {
    if (return_value == -1){ 
        perror(err); 
        exit(1); 
    } 
    return return_value; 
}


int main(int argc, char *argv[]) 
{ 
    if (argc<3) {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }

    int sockfd, portno, n;
    struct sockaddr_in network_addr;
    struct hostent *server;
    char buffer[256];

    portno = atoi(argv[2]);
    sockfd = guard(socket(AF_INET, SOCK_STREAM, 0), "error opening the socket");

    server = gethostbyname(argv[1]);
    if(server == NULL){
        fprintf(stderr,"Error, no such host");
        exit(0);
    }

    bzero((char*) &network_addr, sizeof(network_addr));
    network_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0], (char *)&network_addr.sin_addr.s_addr, server->h_length);
    network_addr.sin_port = htons(portno);

    guard(connect(sockfd, (struct sockaddr*) &network_addr, sizeof(network_addr)), "Connection failed");
    
    while(1){
        bzero(buffer,256); 
        printf("Client: ");
        fgets(buffer,255,stdin);
        guard(write(sockfd, buffer, strlen(buffer)), "error on writing");

        if (strncmp("exit", buffer, 4)==0) break;
    }
    close(sockfd);
    return 0;
}

/* scratch code */
        //read
        // bzero(buffer, 256);
        // n = read(sockfd, buffer, 255);
        // if (n<0) error("error on reading");
        // printf("Server: %s\n", buffer);