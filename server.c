#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <pthread.h>

#define SERVER_COUNT 3 // Define the number of server

// By using thread function, handle client communication
void *handle_client(void *client_socket_ptr) {
    int client_socket = *(int *)client_socket_ptr;
    char buffer[1024];
    long long num; // Used a long long data type because of large numbers
    
    while (1) {
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            break;
        }

        buffer[bytes_received] = '\0';
        sscanf(buffer, "%lld", &num);
        num *= 2;

        printf("Server: Input- %lld, Output(Double number)- %lld\n", num / 2, num); // That is the message(output) displayed in random server page with numbers

        snprintf(buffer, sizeof(buffer), "%lld", num);
        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);
    pthread_exit(NULL);
}

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

