#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdbool.h>

#define SERVER_COUNT 3 // Define the number of server
#define MIN_PORT 1024   // Minimum port number that can be entered
#define MAX_PORT 49151  // Maximum port number that can be entered

int main() {
    char input[1024];
    char buffer[1024];
    struct sockaddr_in server_addr;
    long long num; 

    while (1) {
        int client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket == -1) {
            perror("Socket creation failed"); // Error message
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
    // Connect to a random server
    int selected_server = rand() % SERVER_COUNT;
    if (connect(client_socket, (struct sockaddr *)&server_addrs[selected_server], sizeof(server_addrs[selected_server])) == -1) {
        perror("Failure of connection to server. Try again"); // Error message
        close(client_socket);
        continue; 
    }