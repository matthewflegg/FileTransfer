#include "util/file.h"
#include "util/socket.h"

#define ARGS_COUNT 4
#define PORT_MAX_NUMBER 65535
#define PORT_MIN_NUMBER 5000

/**
 * @brief  Convert a string to an integer. Includes internal error checking.
 * @note   
 * @param  string: The string to convert to and integer.
 * @retval The string converted to an integer.
 */
int to_int(const char* string);

void handle_connection();

/**
 * @brief  The main entry point of the application.
 * @note   
 * @param  argc: The number of command line arguments passed.
 * @param  argv: The command line arguments. Expected in the form ./[executable] <ip> <metadata port> <file port> <queue length>.
 * @retval 0 on successful execution, -1 or none on failure.
 */
int main(int argc, char** argv)
{
    // Declare variables to be used later.
    int server_socket, client_socket, port, queue_length;
    struct sockaddr_in server_address, client_address;
    char* ip;
    char file_name[FILE_NAME_LENGTH_LIMIT];

    // Ensure the correct number of command line arguments have been passed.
    if (argc != ARGS_COUNT) {
        fprintf(stderr, "ERROR: Incorrect number of arguments (%d expected).\n", ARGS_COUNT);
        exit(EXIT_FAILURE);
    }

    // Assign variable values to their respective command line arguments.
    ip = argv[1];
    port = to_int(argv[2]);
    queue_length = argv[3];

    // Check whether the port lies between the minimum and maximum allowed values.
    if (port < PORT_MIN_NUMBER || port > PORT_MAX_NUMBER) {
        fprintf(stderr, "ERROR: Port must be between %d and %d.\n", PORT_MIN_NUMBER, PORT_MAX_NUMBER);
        exit(EXIT_FAILURE);
    }

    // Initialize the sockets by creating them, binding them and instructing them to listen.
    server_socket = socket_create();
    socket_bind(server_socket, ip, port);
    socket_listen(server_socket, queue_length);

    while (true) {
        char file_name[FILE_NAME_LENGTH_LIMIT];
        socklen_t address_size = sizeof server_address;
        struct sockaddr_in client_address;
        int client_socket = socket_accept(server_socket, (struct sockaddr*)&client_address, &address_size);
        save_file_name(client_socket, file_name, FILE_NAME_LENGTH_LIMIT);
        save_file(client_socket, file_name);
    }
}

int to_int(const char* string)
{
    char* end_pointer;
    int result = (int)strtol(string, &end_pointer, 10);

    // Check whether the string passed can be converted to a decimal (base 10) number.
    if (end_pointer == string) {
        fprintf(stderr, "ERROR: String '%s' is not a decimal number.\n", string);
        exit(EXIT_FAILURE);
    }

    // Check whether the string has extra non-convertible characters in it.
    if (*end_pointer != '\0') {
        fprintf(stderr, "ERROR: Extra characters in '%s' at the end of input '%s'.\n", string, end_pointer);
        exit(EXIT_FAILURE);
    }

    return result;
}