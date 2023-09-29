#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_COUNT 3 // Define the number of server

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];
    int num;

    // From this line, the process is about socket creation.
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed"); // It gives an error message when problem occurs.
        exit(EXIT_FAILURE);
    }

    // Configuration of server addresses and ports
    struct sockaddr_in server_addrs[SERVER_COUNT];
    int ports[SERVER_COUNT] = {12345, 12346, 12347}; // defining the port numbers

    for (int i = 0; i < SERVER_COUNT; i++) {
        server_addrs[i].sin_family = AF_INET;
        server_addrs[i].sin_port = htons(ports[i]);
        server_addrs[i].sin_addr.s_addr = inet_addr("127.0.0.1"); //server address
    }