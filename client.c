#include "util/auth.h"
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

    // Create a new socket.
    int client_socket = socket_create();
    printf("INFO: Created socket (FD %d).\n", client_socket);

    // Connect socket to the server and send file name.
    struct sockaddr_in server_address = socket_get_address(ip, port);
    socket_connect(client_socket, &server_address, sizeof server_address);

    // Prompt for credentials.
    char* password_hash = get_user_password_input();
    send_password_hash(client_socket, password_hash);

    send_file_name(client_socket, name_to_save_file_with, sizeof name_to_save_file_with);
    printf("INFO: Connected to server with address %s:%d.\n", ip, port);

    // Send the file to the server.
    FILE* file;

    if ((file = fopen(name_of_file_to_send, "r")) == NULL) {
        fprintf(stderr, "ERROR: Could not read the file.\n");
        return EXIT_FAILURE;
    }

    send_file(client_socket, file);
    printf("INFO: Sent file %s to be saved with name %s.\n", name_of_file_to_send, name_to_save_file_with);

    // Close the socket and exit.
    close(client_socket);
    printf("INFO: Socket (FD %d) connection to server %s:%d closed.\n", client_socket, ip, port);
    return 0;
}