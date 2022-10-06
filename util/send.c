#include "send.h"

void send_file_name(int client_metadata_socket, char* file_name, int file_name_length)
{
    // Ensure the file name does not exceed the max length (OS dependent).
    if (file_name_length > FILE_NAME_LENGTH_LIMIT) {
        fprintf(stderr, "ERROR: Maximum file name length exceeded (%d characters).\n", FILE_NAME_LENGTH_LIMIT);
        exit(EXIT_FAILURE);
    }

    // Send the file name to the server's metadata socket where it will be recorded.
    if (send(client_metadata_socket, file_name, file_name_length, 0) < 0) {
        fprintf(stderr, "ERROR: Could not send the file name to the specfied socket.\n");
        exit(EXIT_FAILURE);
    }
}

void send_file(int client_file_socket, FILE* file_pointer)
{
    char buffer[BUFFER_SIZE];

    // Iteratively read the contents of the file into `buffer` and send it to the server's file socket.
    while (fgets(buffer, BUFFER_SIZE, file_pointer) != NULL) {
        if (send(client_file_socket, buffer, BUFFER_SIZE, 0) < 0) {
            break;
        }

        // Clean up by setting all bytes in the buffer to zero.
        bzero(buffer, BUFFER_SIZE);
    }
}