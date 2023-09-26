#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1" // Define the IP address of the server
#define PORT 12345  // Define the port number of the server

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    // From this line, the process is about socket creation.
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed"); // It gives an error message when problem occurs.
        exit(EXIT_FAILURE);
    }