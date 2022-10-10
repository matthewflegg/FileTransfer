#include "file.h"

void save_file_name(int client_socket, char* file_name_out_param, int file_name_out_param_length)
{
    // Ensure that the file name to write into has enough characters to contain it.
    if (file_name_out_param_length < FILE_NAME_LENGTH_LIMIT) {
        fprintf(stderr, "ERROR: Attempted to write file name into string with insufficient length.\n");
        exit(EXIT_FAILURE);
    }

    // Write the file name into the out parameter specified.
    if (recv(client_socket, file_name_out_param, FILE_NAME_LENGTH_LIMIT, 0) < 0) {
        fprintf(stderr, "ERROR: Could not receive file name.\n");
        exit(EXIT_FAILURE);
    }
}

void save_file(int client_socket, char* file_name)
{
    FILE* file_pointer;
    char buffer[BUFFER_SIZE];

    // Ensure that a new file can be created for writing with the specified name.
    if ((file_pointer = fopen(file_name, "w")) == NULL) {
        fprintf(stderr, "ERROR: Could not save the file `%s`.\n", file_name);
        exit(EXIT_FAILURE);
    }

    // Iteratively receive file contents from the client and write into file `BUFFER_SIZE` bytes per pass.
    while (true) {
        if (recv(client_socket, buffer, BUFFER_SIZE, 0) <= 0) {
            break;
        }

        fprintf(file_pointer, buffer);
        bzero(buffer, BUFFER_SIZE);
    }

    // This is necessary to save any modifications made to the file.
    fclose(file_pointer);
}

void send_file_name(int client_socket, char* file_name, int file_name_length)
{
    // Ensure the file name does not exceed the max length (OS dependent).
    if (file_name_length > FILE_NAME_LENGTH_LIMIT) {
        fprintf(stderr, "ERROR: Maximum file name length exceeded (%d characters).\n", FILE_NAME_LENGTH_LIMIT);
        exit(EXIT_FAILURE);
    }

    // Send the file name to the server's metadata socket where it will be recorded.
    if (send(client_socket, file_name, FILE_NAME_LENGTH_LIMIT, 0) < 0) {
        fprintf(stderr, "ERROR: Could not send the file name to the specfied socket.\n");
        exit(EXIT_FAILURE);
    }
}

void send_file(int client_socket, FILE* file_pointer)
{
    char buffer[BUFFER_SIZE];

    // Iteratively read the contents of the file into `buffer` and send it to the server's file socket.
    while (fgets(buffer, BUFFER_SIZE, file_pointer) != NULL) {
        if (send(client_socket, buffer, BUFFER_SIZE, 0) < 0) {
            break;
        }

        // Clean up by setting all bytes in the buffer to zero.
        bzero(buffer, BUFFER_SIZE);
    }

    // This is necessary to save any modifications made to the file.
    fclose(file_pointer);
}