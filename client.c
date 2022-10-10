#include "util/convert.h"
#include "util/file.h"
#include "util/socket.h"
#include <unistd.h>

#define ARGS_COUNT 5

/**
 * @brief  The main entry point of the application.
 * @note   
 * @param  argc: The number of command line arguments passed.
 * @param  argv: The command line arguments. Expected in the form ./[executable] <ip> <port> <file to read> <filename to save>.
 * @retval 0 on successful execution, -1 or none on failure.
 */
int main(int argc, char** argv)
{
    if (argc != ARGS_COUNT) {
        fprintf(stderr, "ERROR: Incorrect number of arguments (%d expected).\n", ARGS_COUNT);
        return EXIT_FAILURE;
    }

    char* ip = argv[1];
    int port = to_int(argv[2]);
    char* name_of_file_to_send = argv[3];
    char* name_to_save_file_with = argv[4];
    int client_socket = socket_create();
    struct sockaddr_in server_address = socket_get_address(ip, port);
    socket_connect(client_socket, &server_address, sizeof server_address);
    send_file_name(client_socket, name_to_save_file_with, sizeof name_to_save_file_with);
    FILE* file;

    if ((file = fopen(name_of_file_to_send, "r")) == NULL) {
        fprintf(stderr, "ERROR: Could not read the file.\n");
        return EXIT_FAILURE;
    }

    send_file(client_socket, file);
    close(client_socket);
    return 0;
}