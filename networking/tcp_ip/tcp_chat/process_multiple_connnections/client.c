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
#include <sys/wait.h>

#include <netinet/in.h> 
#include <netdb.h> // defines the hostent structure which has host name and ipv4 address
#include <string.h> 

void error(const char *msg){
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) 
{ 
    int sockfd, portno, n;
    struct sockaddr_in network_addr;
    struct hostent *server;
    char buffer[256];
	
    if (argc<3) {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }

    //socket
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("error opening the socket");

    //get hostname
    server = gethostbyname(argv[1]);
    if(server == NULL){
        fprintf(stderr,"Error, no such host");
        exit(0);
    }

    //clear serv_addr
    bzero((char*) &network_addr, sizeof(network_addr));
    network_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0], (char *)&network_addr.sin_addr.s_addr, server->h_length);
    network_addr.sin_port = htons(portno);

    //connect
    if(connect(sockfd, (struct sockaddr*) &network_addr, sizeof(network_addr)) < 0 ){
        error("Connection failed");
    }

    pid_t child_pid;
    //loop
    while(1){
        //write
        bzero(buffer,256); 
        printf("Client: ");
        fgets(buffer,255,stdin);
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) error("error on writing");
        if (strncmp("exit", buffer, 4)==0) break;
        //read
        // bzero(buffer, 256);
        // n = read(sockfd, buffer, 255);  //blocking
        // if (n < 0)
        //     error("error on reading"); //printf("Server sent: %s\n", buffer);
        // else if (n > 0){
        //     child_pid = fork(); //spawn proc for blocking call
        //     if (child_pid < 0){
        //         perror("fork failed");
        //     }
        //     if (child_pid == 0){
        //         if (strcmp(buffer, "exit") == 0){
        //             n = write(sockfd, "exit", 4);
        //             if (n < 0)
        //                 error("error on writing");
        //             close(sockfd);
        //             exit(0);
        //         }
        //         else{
        //             /* in parent */
        //             if (waitpid(child_pid, NULL, 0) < 0){
        //                 perror("Failed to collect child process");
        //                 break;
        //             }
        //         }
        //     }
            
        // }


    }

    close(sockfd);
    return 0;

}
