#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define SERVER_COUNT 3 // Define the number of server

void handle_client(int client_socket) {
    char buffer[1024];
    int num;


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int client_socket, server_socket;
    struct client_addr, sockaddr_in server_addr;
    socklen_t client_len = sizeof(client_addr);
    int port = atoi(argv[1]);

    // Creation of a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Failure of socket creation. Try again!");
        exit(EXIT_FAILURE);
    }

