#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#define DATA_BUFFER 1024
#define MAX_MESSAGES 3

int main(int argc, char *argv[])
{
    WSADATA wsa_data;
    SOCKET sock_client;
    int server_port = 5050;
    struct sockaddr_in server_addr;

    char client_message[DATA_BUFFER];
    int send_data_len;
    int receive_data_len;
    char receive_data[DATA_BUFFER];

    if (argc < 2)
    {
        printf("Usage: %s <server_ip>\n", argv[0]);
        return 1;
    }

    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        printf("Failed to load Winsock.\n");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    sock_client = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_client == INVALID_SOCKET)
    {
        printf("Failed to create socket: %d\n", WSAGetLastError());
        return -1;
    }

    if (connect(sock_client, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("Failed to connect to server: %d\n", WSAGetLastError());
        return -1;
    }

    for (int i = 0; i < MAX_MESSAGES; ++i)
    {
        printf("Enter message (type 'exit' to quit): ");
        fgets(client_message, DATA_BUFFER, stdin);

        size_t len = strlen(client_message);
        if (len == 0)
        {
            continue;
        }

        if (len > 0 && client_message[len - 1] == '\n')
        {
            client_message[len - 1] = '\0';
        }

        if (strcmp(client_message, "exit") == 0)
        {
            break;
        }
        send_data_len = send(sock_client, client_message, len, 0);

        if (send_data_len == SOCKET_ERROR)
        {
            printf("Failed to send data: %d\n", WSAGetLastError());
            break;
        }
        printf("Sent data bytes: %d\n", send_data_len);

        memset(receive_data, 0, sizeof(receive_data));
        receive_data_len = recv(sock_client, receive_data, sizeof(receive_data), 0);
        if (receive_data_len == SOCKET_ERROR)
        {
            printf("Failed to receive data: %d\n", WSAGetLastError());
            break;
        }
        if (receive_data_len == 0)
        {
            printf("Server closed the connection\n");
            break;
        }
        else
        {
            printf("Received data bytes: %d\n", receive_data_len);
            printf("Received data: %s\n", receive_data);
        }
    }

    closesocket(sock_client);
    WSACleanup();
    return 0;
}