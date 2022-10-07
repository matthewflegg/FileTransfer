#include "endpoint.h"

endpoint_t* endpoint_create()
{
    endpoint_t* endpoint = malloc(sizeof *endpoint);
    endpoint->metadata_socket = socket(AF_INET, SOCK_STREAM, 0);
    endpoint->file_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (endpoint->metadata_socket < 0 || endpoint->file_socket < 0) {
        fprintf(stderr, "ERROR: Could not create both necessary sockets.\n");
        exit(EXIT_FAILURE);
    }
}

void endpoint_bind(endpoint_t* endpoint, int ip, int metadata_port, int file_port)
{
    _bind_socket_to_address(endpoint->metadata_socket, _create_address(ip, metadata_port));
    _bind_socket_to_address(endpoint->file_socket, _create_address(ip, file_port));
}

void endpoint_listen()
{

}

void endpoint_delete(endpoint_t* endpoint)
{
    free(endpoint);
    endpoint = NULL;
}

struct sockaddr_in* _create_address(char* ip, int port)
{
    struct sockaddr_in* address;
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    
    if (inet_aton(ip, &address->sin_addr) == 0) {
        fprintf(stderr, "ERROR: Could not convert the specified IP to binary.\n");
        exit(EXIT_FAILURE);
    }
    
    return address;
}

void _bind_socket_to_address(int sock, struct sockaddr_in* address)
{
    if (bind(sock, (struct sockaddr*)address, sizeof *address) < 0) {
        fprintf(stderr, "ERROR: Could not bind the specified socket to an address.\n");
        exit(EXIT_FAILURE);
    }
}