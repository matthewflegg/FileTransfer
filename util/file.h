#ifndef FILE_H
#define FILE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024            /* Max read/write buffer size in bytes */
#define FILE_NAME_LENGTH_LIMIT 255  /* Max file name length in bytes on Linux */

/**
 * @brief  Saves a file name received from a client's socket.
 * @note
 * @param  client_socket: The client's socket.
 * @param  file_name_out_param: Empty variable which will be assigned the value of the client's chosen filename.
 * @param  file_name_out_param_length: The length of the string which will be assigned the filename.
 * @retval None
 */
void save_file_name(int client_socket, char* file_name_out_param, int file_name_out_param_length);

/**
 * @brief  Saves a file received from a client's socket.
 * @note
 * @param  client_socket: The client's socket.
 * @param  file_name: The name of the file to send.
 * @retval None
 */
void save_file(int client_socket, char* file_name);

/**
 * @brief  Sends a file name to a client's socket.
 * @note
 * @param  client_socket: The client's socket.
 * @param  file_name: The name of the file to be sent.
 * @param  file_name_length: The number of characters in the file name.
 * @retval None
 */
void send_file_name(int client_socket, char* file_name, int file_name_length);

/**
 * @brief  Sends a file to a client's socket.
 * @note
 * @param  client_socket: The client's socket.
 * @param  file_pointer: A pointer to the file to send. Must be opened with 'r' or 'rb'
 * @retval None
 */
void send_file(int client_socket, FILE* file_pointer);

#endif