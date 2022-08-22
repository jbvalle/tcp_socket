#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// socket API
#include <sys/types.h>
#include <sys/socket.h>

// for storing address information
#include <netinet/in.h>

// for inet_addr
#include <arpa/inet.h>

// for close
#include <unistd.h>

int main(int argc, char **argv){


    // 1. Create Server Socket
    // socket(int DOMAIN, int TYPE, int PROTOCOL) -> int fd
    // DOMAIN = AF_INET ... describes address type ipv4
    // TYPE = SCOK_STREAM ... describes TCP Socket will be applied
    // PROTOCOL = 0 ... declares TCP will be used
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //  2. Define address struct -> for server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("192.168.0.175");

    // 3. Bind server program to ip address that should be listening
    // Check if listening port is still active and allow reusing PORT
    int reuse = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0){

        perror("Setting Socket Option Failed!\n");
    }
        
    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    // 4. Start listening for connections
    // listen(int listening_socket_fd, int number_of_connecting_clients)
    listen(server_socket, 5);

    // 5. Accept connection
    // int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // 6. Send actual data
    char msg_buff[256]; bzero(msg_buff, 256);

    //========================= TRANSMITTING PROCEDURE =========================
    strcpy(msg_buff, "Server Connection has been established \n");

    send(client_socket, msg_buff, sizeof(msg_buff), 0); bzero(msg_buff, 256);

    for(;;){
        
        //========================== RECEIVING PROCEDURE ===========================
        recv(client_socket, msg_buff, sizeof(msg_buff), 0);

        printf("Recieved: %s", msg_buff); bzero(msg_buff, 256);

    }

    //==========================================================================
    close(server_socket);
    
    return 0;
}

