#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5556
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

int parse_input(char *buffer)
{
    if (buffer[0] == 'c' && buffer[1] == 'l' && buffer[2] == 'i' && buffer[3] == 'e' && buffer[4] == 'n' && buffer[5] == 't' && buffer[6] == '-' && buffer[7] == '5' && buffer[8] == ':')
    {

        return 1;
    }
    else
    {
        return 0;
    }
}
int main()
{

    while (1)
    {
        int client_socket;
        struct sockaddr_in server_address;
        char buffer[1024];

        client_socket_init(&client_socket);

        server_connection(&client_socket, &server_address);

        // User input

        printf("=========================================================== \nEnter tickets in this format\n\nclient-A:B \n\nwhere \nA = client id(5) \nB = number of tickets to be booked \n\nEnter QUIT to quit\n=========================================================== \n ");

        scanf("\n%[^\n]s", buffer);

        if (strcmp(buffer, "QUIT") == 0)
        {
            break;
        }

        if (parse_input(buffer))
        {
            for (int i = 9; i < strlen(buffer); i++)
            {
                if (buffer[i] < '0' || buffer[i] > '9')
                {
                    printf("Invalid Input\n");
                    break;
                }
            }

            // Send data to the server

            if (send(client_socket, buffer, strlen(buffer), 0) > 0)
            {
                printf("Data sent to the server \n");
            }
            else
            {
                printf("Error: Failed to send data to server \n");
            }

            bzero(buffer, 256);

            // Receive data from the server

            if (recv(client_socket, buffer, 1024, 0) > 0)
            {
                printf("Data received from the server: %s \n", buffer);
            }
            else
            {
                printf("Error: Failed to receive data from server \n");
            }

            // Printing the output and closing the connection
            printf("%s\n", buffer);
        }
        else
        {
            printf("Invalid Input\n");
            continue;
        }

        // Close client socket
        close(client_socket);
    }

    return 0;
}
