#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#define DEFAULT_PORT 5050
#define DATA_BUFFER 1024

SOCKET sock_listen;

void signal_handler(int signal)
{
    printf("press on Ctrl+C, clean...\n");
    closesocket(sock_listen);
    WSACleanup();
    exit(0);
}

void *client_handler(void *arg)
{
    SOCKET client_socket = *((SOCKET *)arg);
    struct sockaddr_in client_addr;

    char receive_data[DATA_BUFFER];
    int receive_data_size;
    int client_addr_len = sizeof(client_addr);

    if (getpeername(client_socket, (struct sockaddr *)&client_addr, &client_addr_len) == 0)
    {
        printf("Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    }
    else
    {
        perror("Failed to get client address");
        return NULL;
    }

    while ((receive_data_size = recv(client_socket, receive_data, sizeof(receive_data), 0)) > 0)
    {
        printf("Received from %s:%d: %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), receive_data);
        send(client_socket, receive_data, receive_data_size, 0);
    }

    printf("Client %s:%d disconnected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    closesocket(client_socket);
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char *argv[])
{
    WSADATA wsa_data;
    SOCKET sock_accept;
    int server_port = DEFAULT_PORT;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len;

    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        printf("Failed to load Winsock.\n");
        return -1;
    }

    sock_listen = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_listen == INVALID_SOCKET)
    {
        printf("Failed to create socket: %d\n", WSAGetLastError());
        return -1;
    }

    signal(SIGINT, signal_handler);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock_listen, (LPSOCKADDR)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("Failed to bind socket: %d\n", WSAGetLastError());
        return -1;
    }
    if (listen(sock_listen, 5) == SOCKET_ERROR)
    {
        printf("Failed to listen socket: %d\n", WSAGetLastError());
        return -1;
    }

    client_addr_len = sizeof(client_addr);
    while (1)
    {
        sock_accept = accept(sock_listen, (LPSOCKADDR)&client_addr, &client_addr_len);
        if (sock_accept == INVALID_SOCKET)
        {
            printf("Failed to accept socket: %d\n", WSAGetLastError());
            break;
        }

        pthread_t client_thread;
        if (pthread_create(&client_thread, NULL, client_handler, (void *)&sock_accept) != 0)
        {
            printf("Failed to create client thread\n");
            break;
        }
        pthread_detach(client_thread);
    }

    closesocket(sock_listen);
    WSACleanup();
    return -1;
}