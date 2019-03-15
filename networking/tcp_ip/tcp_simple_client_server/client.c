#include <stdio.h>
#include <stdlib.h>

//to include socket API
#include <sys/types.h>
#include <sys/socket.h>

//header file for connection
#include <netinet/in.h>

int main()
{
    //1. create a socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0); //AF_INET: internet, SOCK_STREAM:TCP protocol, 0:default protocol(TCP)


    //specify the address structure for socket -- need an address to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);              //convert the integer to right network byte order     
    server_address.sin_addr.s_addr = INADDR_ANY; //0.0.0.0

    //2. connect to another socket 
    int connection_status = connect(network_socket,(struct sockaddr*) &server_address,sizeof(server_address));
    //check for error with the connection
    if (connection_status == -1) {
        printf("There was an error making a connection to the remote socket \n\n");
    }
    
    //3. receive response from the server
    char server_response[256]; // to hold the reponse from the server
    recv(network_socket, &server_response, sizeof(server_response), 0);

    //print out the server's response
    printf("the server sent the data: %s\n", server_response);

    close(network_socket);

    return 0;
}
