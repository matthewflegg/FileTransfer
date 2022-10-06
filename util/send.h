#ifndef SEND_H
#define SEND_H

#include "shared.h"

/**
 * @brief  Sends a file name to a client's metadata socket.
 * @note
 * @param  client_metadata_socket: The client's metadata socket.
 * @param  file_name: The name of the file to be sent.
 * @param  file_name_length: The number of characters in the file name.
 * @retval None
 */
void send_file_name(int client_metadata_socket, char* file_name, int file_name_length);

/**
 * @brief  Sends a file to a client's file socket.
 * @note
 * @param  client_file_socket: The client's file socket.
 * @param  file_pointer: A pointer to the file to send. Must be opened with 'r' or 'rb'
 * @retval None
 */
void send_file(int client_file_socket, FILE* file_pointer);

#endif  // SEND_H