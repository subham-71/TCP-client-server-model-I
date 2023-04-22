#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5555

void reverse_string(char *str, int len)
{
    int i = 0, j = len - 1;
    while (i < j)
    {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
void handle_client(int client_socket)
{
    char buffer[1024];
    int read_size = recv(client_socket, buffer, sizeof(buffer), 0);

    printf("[NEW CONNECTION] Client connected\n");

    while (read_size > 0)
    {

        // Reverse the string
        reverse_string(buffer, read_size);

        // Send the reversed string back to the client
        send(client_socket, buffer, read_size, 0);

        // Check read_size
        read_size = recv(client_socket, buffer, sizeof(buffer), 0);
    }

    // Close the client socket
    close(client_socket);

    printf("[DISCONNECTED] Client disconnected\n");
}

int main()
{
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    int address_length = sizeof(server_address);

    // Create a server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        printf("Error: Failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    // Bind the server socket to the port
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        printf("Error: Failed to bind socket\n");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming client connections
    if (listen(server_socket, 5) == -1)
    {
        printf("Error: Failed to listen for connections\n");
        exit(EXIT_FAILURE);
    }

    printf("[LISTENING] Server is listening on port %d\n", PORT);

    while (1)
    {
        // Accept an incoming client connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, (socklen_t *)&address_length);
        if (client_socket == -1)
        {
            printf("Error: Failed to accept connection\n");
            continue;
        }

        // Create a new thread to handle the client connection
        if (fork() == 0)
        {
            // This is the child process, handle the client connection
            close(server_socket);
            handle_client(client_socket);
            exit(EXIT_SUCCESS);
        }
        else
        {
            // This is the parent process, close the client socket and continue listening for connections
            close(client_socket);
        }
    }

    return 0;
}
