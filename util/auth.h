#ifndef AUTH_H
#define AUTH_H

#include <crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 1024

char* get_user_password_input();

void send_password_hash(int client_socket, char password_hash[MAX_PASSWORD_LENGTH]);

void receive_password_hash(int client_socket, char password_hash_out_param[MAX_PASSWORD_LENGTH]);

void overwrite_password_if_none_set(char password_hash[MAX_PASSWORD_LENGTH]);

void validate_password(char password_hash[MAX_PASSWORD_LENGTH]);

#endif