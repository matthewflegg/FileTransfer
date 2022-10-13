#include "socket.h"

int socket_create()
{
    int sock;

    // Ensure that the socket can be given a file descriptor.
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "ERROR: Could not create the socket.\n");
        exit(EXIT_FAILURE);
    }

    return sock;
}

void socket_bind(int sock, char* ip, int port)
{
    // Create an address to bind the socket to.
    struct sockaddr_in address = socket_get_address(ip, port);

    // Bind the socket to a host IPv4 address and port number.
    if (bind(sock, (struct sockaddr*)&address, sizeof address) < 0) {
        fprintf(stderr, "ERROR: Could not bind the socket to the IP %s and port %d.\n", ip, port);
        exit(EXIT_FAILURE);
    }
}

void socket_listen(int sock, int queue_length)
{
    // Instruct the TCP/IP protocol to start listening for connections on this socket.
    if (listen(sock, queue_length) < 0) {
        fprintf(stderr, "ERROR: Could not instruct the socket to listen for connections.\n");
        exit(EXIT_FAILURE);
    }
}

int socket_accept(int sock, struct sockaddr* address_out_param, socklen_t* address_length_out_param)
{
    int connected_socket;

    // Accept a connection from a client, then return its socket file descriptor, address and address length.
    if ((connected_socket = accept(sock, address_out_param, address_length_out_param)) < 0) {
        fprintf(stderr, "ERROR: Could not accept a connection.\n");
        exit(EXIT_FAILURE);
    }

    return connected_socket;
}

void socket_connect(int sock, struct sockaddr_in* target_address, socklen_t target_address_length)
{
    // Connect the socket to a target address.
    if (connect(sock, (struct sockaddr*)target_address, target_address_length) < 0) {
        fprintf(stderr, "ERROR: Could not connect to the specified address.\n");
        exit(EXIT_FAILURE);
    }
}

struct sockaddr_in socket_get_address(char* ip, int port)
{
    // Create an address from the host and port.
    struct sockaddr_in address;
    bzero(&address, sizeof address);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    // Convert the IPv4 address from a string to binary.
    if (inet_aton(ip, &address.sin_addr) <= 0) {
        fprintf(stderr, "ERROR: Could not convert the IPv4 address %s to binary.\n", ip);
        exit(EXIT_FAILURE);
    }

    return address;
}

void socket_close_client(int sock, pthread_t thread_id)
{
    close(sock);
    printf("    [TID %lu] INFO: Closed client socket (FD: %d).\n", thread_id, sock);
}