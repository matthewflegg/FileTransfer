#ifndef AUTH_H
#define AUTH_H

#include <crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/socket.h>
#include <unistd.h>
#include "file.h"

#define MAX_PASSWORD_LENGTH 1024
#define PASSWORD_FILE_NAME "password.txt"

char* get_user_password_input();

void send_password_hash(int client_socket, char password_hash[MAX_PASSWORD_LENGTH]);

void receive_password_hash(int client_socket, char password_hash_out_param[MAX_PASSWORD_LENGTH]);

void overwrite_password_if_none_set(char password_hash[MAX_PASSWORD_LENGTH]);

/**
 * @brief  Validates whether a password is correct.
 * @note
 * @param  password_hash: The hash of the password to validate.
 * @retval true if password is valid, else false.
*/
bool validate_password(char password_hash[MAX_PASSWORD_LENGTH]);

#endif