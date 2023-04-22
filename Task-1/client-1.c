#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5555
#define IP "127.0.0.1"

void client_socket_init(int *client_socket)
{
    // Create a client socket
    *client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (*client_socket == -1)
    {
        printf("Error: Failed to create socket\n");
        exit(EXIT_FAILURE);
    }
}

void server_connection(int *client_socket, struct sockaddr_in *server_address)
{
    // Connect to the server
    server_address->sin_family = AF_INET;
    server_address->sin_addr.s_addr = inet_addr(IP); // Replace with the IP address of your server
    server_address->sin_port = htons(PORT);

    if (connect(*client_socket, (struct sockaddr *)server_address, sizeof(*server_address)) == -1)
    {
        printf("Error: Failed to connect to server \n");
    }
    else
    {
        printf("Connected to server \n");
    }
}

int main()
{
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[1024];

    client_socket_init(&client_socket);

    server_connection(&client_socket, &server_address);

    // Send a string message to the server
    printf("Enter a string to send to the server \n");
    fgets(buffer, sizeof(buffer), stdin);
    send(client_socket, buffer, strlen(buffer), 0);

    // Receive the reversed message from the server
    int read_size = recv(client_socket, buffer, sizeof(buffer), 0);
    if (read_size == -1)
    {
        printf("Error: Failed to receive message from server\n");
        exit(EXIT_FAILURE);
    }

    // Print the reversed message on the console
    printf("Reversed string received from server: %.*s \n \n ", read_size, buffer);

    // Close client socket
    close(client_socket);

    return 0;
}
