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

    // 1. Create Socket
    // by using socket() this returns a fd
    int network_socket;
    // socket(int DOMAIN, int TYPE, int PROTOCOL) -> int fd
    // DOMAIN = AF_INET ... describes address type ipv4
    // TYPE = SCOK_STREAM ... describes TCP Socket will be applied
    // PROTOCOL = 0 ... declares TCP will be used
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Connect to another socket with connect()
    // Prerequisit: Specify an address first to connect as well as a port thats why inet header was needed to provide Address structure
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    //server_address.sin_addr.s_addr = inet_addr("176.66.244.167");
    server_address.sin_addr.s_addr = inet_addr("192.168.0.175");
    //server_address.sin_addr.s_addr = INADDR_ANY;

    int conn_stat = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    //Error Handling connect() == 0 all worked well
    if(conn_stat == -1){

        fprintf(stderr, "Connection could not be established\n");
        exit(EXIT_FAILURE);
    }

    // 3. Recieve Data once the connection was established
    // Buffer for storing server_data
    char msg_buff[256]; bzero(msg_buff, 256);
    

    //========================== RECEIVING PROCEDURE ===========================
    recv(network_socket, msg_buff, sizeof(msg_buff), 0);

    printf("Recieved: %s", msg_buff); bzero(msg_buff, 256);

    //========================= TRANSMITTING PROCEDURE =========================
    //printf("Send: "); for(int n = 0; (msg_buff[n++] = getchar()) != '\n';);
    
    strcpy(msg_buff, argv[1]);

    send(network_socket, msg_buff, sizeof(msg_buff), 0); bzero(msg_buff, 256);


    //==========================================================================
    close(network_socket);
    return 0;
}
