#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define RCV_PORT_SIMULATOR 20001
#define SEND_PORT_SIMULATOR 20000
#define RCV_PORT 30000
#define SEND_PORT 20008
#define BUFFER_SIZE 1024
#define FROMWHO_ADRESS "10.100.23.11"

// Eskil prøvde serveren hjemme
#define IP_LOCAL_ESKIL "172.26.161.38"

void reciever();
void sender();
void broadcast();

int main() {
    printf("\nHello, World!\n");

    //sender();
    //reciever();
    broadcast();

    return 0;
}


void reciever() {
 
    //initializes variables for receiving
    uint8_t buffer[BUFFER_SIZE];
    int receiving = 1;
    struct sockaddr_in fromWho;
    
    //initializes socket and address
    struct sockaddr_in Adress;
    Adress.sin_port = htons(RCV_PORT);
    Adress.sin_family = AF_INET;
    Adress.sin_addr.s_addr = inet_addr("0.0.0.0");
    int fd_recvSocket = socket(AF_INET, SOCK_DGRAM, 0);



    // La til denne for å prøve simulatoren
    //setsockopt(fd_recvSocket, SOL_SOCKly = AF_INET, SO_REUSEADDR, NULL, (socklen_t) NULL);
    
    
    if (bind(fd_recvSocket, (struct sockaddr*) &Adress, sizeof(struct sockaddr)) < 0){
        printf("\nError: Connect failed, and Casper is not happy\n");
        exit(0);
    };


    while (receiving) {
        
        socklen_t tmp = sizeof(fromWho);
        recvfrom(fd_recvSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &fromWho,\
        &tmp); 
        
        //Interprets message
        for (int i = 0; i < 1024; i++){
            if (buffer[i] == '\0') {
                break;
            }
            printf("%c", buffer[i]);
        } 
        printf("\n");
      
    }
};

void sender() {

    //initializes variables for sending
    char message[] = "Hans Tomren liker ikke UDP";
    int sending = 1;


    // Init socket / address
    struct sockaddr_in DestAddr; 
    DestAddr.sin_addr.s_addr = inet_addr(FROMWHO_ADRESS);
    DestAddr.sin_port = htons(SEND_PORT);
    DestAddr.sin_family = AF_INET;
    int fd_sendSocket = socket(AF_INET, SOCK_DGRAM, 0);


    socklen_t tmp = sizeof(DestAddr);
    sendto(fd_sendSocket, &message, sizeof(message), 0, (struct sockaddr*) &DestAddr, tmp);

};

void broadcast() {
    char message[] = "Hans Tomren liker ikke UDP BROADCAST";
    int enable = 1;

    // Init things
    struct sockaddr_in BroadcastAddr;
    in_addr_t broadcastIP = inet_addr("255.255.255.255");
    BroadcastAddr.sin_addr.s_addr = broadcastIP;
    BroadcastAddr.sin_family = AF_INET;
    BroadcastAddr.sin_port = htons(SEND_PORT);
    int fd_broadcastSocket = socket(AF_INET, SOCK_DGRAM, 0);

    setsockopt(fd_broadcastSocket, SOL_SOCKET, SO_BROADCAST, &enable, sizeof(enable));

    socklen_t tmp = sizeof(BroadcastAddr);
    sendto(fd_broadcastSocket, &message, sizeof(message), 0, (struct sockaddr*) &BroadcastAddr, tmp);

}

