#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT_RECV 34933
#define PORT_RECV_DELIM 33546
#define BUFFER_SIZE 1024
#define ADDR_SERVER "10.100.23.11"

void tcpChannel();

int main(){

    tcpChannel();

    return 0;
}

void tcpChannel() {

    // Initialize tingtang
    char inBuffer[BUFFER_SIZE];
    char message[BUFFER_SIZE] = "TCP Connection Complete from lab 8"; 

    // Initialize Socket / Address
    struct sockaddr_in ClientAddr;
    ClientAddr.sin_port = htons(PORT_RECV);
    ClientAddr.sin_family = AF_INET;
    ClientAddr.sin_addr.s_addr = inet_addr(ADDR_SERVER);
    int fd_recvSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (connect(fd_recvSocket, (struct sockaddr*) &ClientAddr, sizeof(struct sockaddr)) != 0 ) {
        printf("\nERROR: Connection to the server failed\n");
    }
    else {
        printf("\nConnected\n");
    }

    
    recv(fd_recvSocket, &inBuffer, BUFFER_SIZE, 0);
    // Writes the message to the terminal
    printf("\n");
    for (int i = 0; i < BUFFER_SIZE; i++){
        if (inBuffer[i] == '\0') {
            break;
        }
        printf("%c", inBuffer[i]);
    } 
    printf("\n");


    
    send(fd_recvSocket, &message, BUFFER_SIZE, 0);


    recv(fd_recvSocket, &inBuffer, BUFFER_SIZE, 0);
    
    printf("\n");
    for (int i = 0; i < BUFFER_SIZE; i++){
        if (inBuffer[i] == '\0') {
            break;
        }
        printf("%c", inBuffer[i]);
    } 
    printf("\n");
    
}