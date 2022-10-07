#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

typedef struct
{
    int metadata_socket;
    int file_socket;

} endpoint_t;

endpoint_t* endpoint_create();

#endif