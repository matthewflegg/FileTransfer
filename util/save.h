#ifndef SAVE_H
#define SAVE_H

#include "shared.h"

/**
 * @brief  Saves a file name received from a client's metadata socket.
 * @note
 * @param  client_metadata_socket: The client's metadata socket.
 * @param  file_name_out_param: Empty variable which will be assigned the value of the client's chosen filename.
 * @param  file_name_out_param_length: The length of the string which will be assigned the filename.
 * @retval None
 */
void save_file_name(int client_metadata_socket, char* file_name_out_param, int file_name_out_param_length);

/**
 * @brief  Saves a file received from a client's file socket.
 * @note
 * @param  client_file_socket: The client's metadata socket.
 * @param  file_name: The name of the file to send.
 * @retval None
 */
void save_file(int client_file_socket, char* file_name);

#endif