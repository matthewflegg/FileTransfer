/**
 * Wrapper for the socket functions found in the C standard library.
 * 
 * These functions implement behaviour and error checking/outputs specific
 * to this application.
 */

#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

/**
 * @brief  Create a new socket. Handles errors internally.
 * @note   
 * @retval The file descriptor of the new socket.
 */
int socket_create();

/**
 * @brief  Bind a socket to an IPv4 address and port number. Handles errors internally.
 * @note   
 * @param  sock: The socket to bind.
 * @param  ip: The IPv4 address to bind the socket to.
 * @param  port: The port to bind the socket to.
 * @retval None
 */
void socket_bind(int sock, const char* ip, const int port);

/**
 * @brief  Instructs a socket to listen for connections. Handles errors internally.
 * @note   
 * @param  sock: The socket to instruct to listen to connections.
 * @param  queue_length: The number of clients that can wait for a connection to this socket.
 * @retval None
 */
void socket_listen(int sock, const int queue_length);

/**
 * @brief  Accepts a connection from a client. Handles errors internally.
 * @note   
 * @param  sock: The socket to accept the connection to. 
 * @param  address_out_param: Out parameter. This will be set to the address of the connecting peer.
 * @param  address_length_out_param: Out parameter. This will be set to the length of the connecting peer's address.
 * @retval The client's socket file descriptor.
 */
int socket_accept(int sock, struct sockaddr* address_out_param, socklen_t* address_length_out_param);

/**
 * @brief  Connects a socket to a target address.
 * @note   
 * @param  sock: The socket that will be connected to the target.
 * @param  target_address: The address of the socket to connect to.
 * @param  target_address_length: The length of the address.
 * @retval None
 */
void socket_connect(int sock, struct sockaddr_in* target_address, socklen_t target_address_length);

#endif