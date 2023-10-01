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

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    int port = atoi(argv[1]);

    // Creation of a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Failure of socket creation. Try again!"); // Error message
        exit(EXIT_FAILURE);
    }
    // Configuration of server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Socket binding is failed"); // Error message
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 3) == -1) {
        perror("Server listening is failed"); // Error message
        exit(EXIT_FAILURE);
    }

    printf("Server is currently on port %d\n", port); // If connection to the port is successful, Print this message.

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1) {
            perror("Client connection is not accepted. Try again!"); // Error message
            continue;
        }

        // Thread creation for handling our client
        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_client, &client_socket) != 0) {
            perror("Thread creation is failed. Try again!"); // Error message if creation is failed
            close(client_socket);
        }
    }
    close(server_socket);

    return 0;
}

