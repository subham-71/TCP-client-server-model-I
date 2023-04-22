#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 5556
#define IP "127.0.0.1"

int book_tickets(int client_socket)
{

    int server_records = open("server_records.txt", O_RDONLY);

    // Get the ticket available info
    
    off_t pos = lseek(server_records, 0, SEEK_END) - 1;
    while (pos > 0)
    {
        lseek(server_records, pos, SEEK_SET);

        char ch;
        read(server_records, &ch, 1);

        if (ch == ']')
        {
            break;
        }
        pos--;
    }

    // Read the last line of the file
    char last_line[1024];
    int x = pread(server_records, last_line, 1024, pos);

    int tickets_available = 0;

    char *position = strstr(last_line, ":");
    sscanf(position + 1, "%d", &tickets_available);

    char buffer[1024];
    bzero(buffer, 1024);

    // Receiving request from client

    int client_tickets = 0;
    int client_id;

    if (recv(client_socket, buffer, 1024, 0) >= 0)
    {

        char *pos_1 = strstr(buffer, ":");
        char *str = strstr(buffer, "-");
        client_id = str[1] - '0';
        sscanf(pos_1 + 1, "%d", &client_tickets);
    }
    else
    {
        perror("Error on Receiving Buffer.\n");
        return -1;
    }

    if (client_tickets > tickets_available)
    {
        strcpy(buffer, "NOT ENOUGH TICKETS AVAILABLE ! ");
    }
    else
    {

        tickets_available = tickets_available - client_tickets;
        char client_message[1024];
        sprintf(client_message, "Tickets Booked : %d  \nTickets Now Available : %d\n", client_tickets, tickets_available);
        strcpy(buffer, client_message);

        int write_records = open("server_records.txt", O_WRONLY | O_APPEND);
        if (write_records != -1)
        {

            char booking_record[1024];
            sprintf(booking_record, "\nClient %d booked : %d\n", client_id, client_tickets);
            write(write_records, booking_record, strlen(booking_record));

            char tickets_available_now[1024];
            sprintf(tickets_available_now, "\n[INFO] Tickets Available : %d\n", tickets_available);
            write(write_records, tickets_available_now, strlen(tickets_available_now));

            close(write_records);
        }
        else
        {
            perror("Failed to open file");
            exit(0);
        }
    }

    // Sending response to client

    if (send(client_socket, buffer, strlen(buffer), 0) >= 0)
    {
        printf("Sent to client successfully.\n");
    }
    else
    {
        perror("Error on Sending Buffer.\n");
        return -1;
    }

    bzero(buffer, 1024);
    return 0;
}

int handle_client(int client_socket)
{

    printf("[NEW CONNECTION] Client connected\n");

    int x = book_tickets(client_socket);

    close(client_socket);

    // Close the client socket

    printf("[DISCONNECTED] Client disconnected\n");
    exit(0);
    return x;
}

void server_socket_create(int *server_socket)
{

    *server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Create a server socket
    *server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (*server_socket == -1)
    {
        printf("Error: Failed to create socket\n");
        exit(EXIT_FAILURE);
    }
}

int handle_auth()
{
    printf("Enter user_id : ");
    char user_id[1024];
    scanf("%s", user_id);

    printf("Enter password : ");
    char password[1024];
    scanf("%s", password);

    if (strcmp(user_id, "admin") != 0 || strcmp(password, "password") != 0)
    {
        printf("Authentication Failed !\n");
        return -1;
    }
    else
    {
        printf("Authentication Successful !\n===============================================================\n");
        return 0;
    }
}

int main()
{

    while (1)
    {
        if (handle_auth() == -1)
        {
            continue;
        }

        int server_socket, client_socket;
        struct sockaddr_in server_address, client_address;
        int address_length = sizeof(server_address);

        // Create a server socket
        server_socket_create(&server_socket);

        // Bind the server socket to the port

        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = inet_addr(IP);
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
                pthread_mutex_t mutex;
                pthread_mutex_lock(&mutex);

                int x = handle_client(client_socket);
                if (x = -1)
                {
                    continue;
                }

                pthread_mutex_unlock(&mutex);
            }
            else
            {
                // This is the parent process, close the client socket and continue listening for connections
                close(client_socket);
                continue;
            }
        }

        // Close the server socket
        close(server_socket);

        return 0;
    }
}
