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
        printf("Connected to a random server on port %d\n", ntohs(server_addrs[selected_server].sin_port));

        printf("Enter a number (or 'e' to exit): ");
        if (scanf("%s", input) != 1) {
            break; // Exit the loop if input is not readable
        }

        if (strcmp(input, "e") == 0) {
            // This gives us the opportunity to exit by using the "e" key. Type e and press enter if you want to quit.
            break;
        }

        if (sscanf(input, "%lld", &num) != 1) {
            printf("Incorrect input. Please enter a number correctly or write 'e' then press enter if you want to quit.\n"); // When there is no number as a input, print this message.
            close(client_socket);
            continue; 
        }
        snprintf(buffer, sizeof(buffer), "%lld", num);
        send(client_socket, buffer, strlen(buffer), 0);

        recv(client_socket, buffer, sizeof(buffer), 0);
        printf("Server response: %s\n", buffer);

        close(client_socket); 
    }

        return 0;
}