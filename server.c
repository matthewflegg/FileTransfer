#include "util/file.h"
#include "util/socket.h"
#include <string.h>

#define ARGS_COUNT 5
#define PORT_MAX_NUMBER 65535
#define PORT_MIN_NUMBER 5000

/**
 * @brief  Convert a string to an integer. Includes internal error checking.
 * @note   
 * @param  string: The string to convert to and integer.
 * @retval The string converted to an integer.
 */
int to_int(const char* string);

/**
 * @brief  Check if a port number lies between PORT_MIN_NUMBER and PORT_MAX_NUMBER.
 * @note   
 * @param  port: The port to validate.
 * @retval None
 */
void validate_port(int port);

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
    int meta_socket, file_socket;
    int meta_port, file_port;
    int queue_length;
    char* ip;

    // Ensure the correct number of command line arguments have been passed.
    if (argc != ARGS_COUNT) {
        fprintf(stderr, "ERROR: Incorrect number of arguments (%d expected).\n", ARGS_COUNT);
        exit(EXIT_FAILURE);
    }

    // Assign variable values to their respective command line arguments.
    ip = argv[1];
    meta_socket = to_int(argv[2]);
    file_socket = to_int(argv[3]);
    queue_length = argv[4];

    // Validate the ports specified to ensure they're in the permitted range.
    validate_port(meta_socket);
    validate_port(file_socket);

    // Initialize the sockets by creating them, binding them and instructing them to listen.
    socket_server_init(meta_socket, ip, meta_port, queue_length);
    socket_server_init(file_socket, ip, file_port, queue_length);
}

int to_int(const char* string)
{
    char* end;
    int integer = (int)strtol(string, &end, 10);

    // Check whether the string passed can be converted to a decimal (base 10) number.
    if (end == string) {
        fprintf(stderr, "ERROR: String '%s' is not a decimal number.\n", string);
        exit(EXIT_FAILURE);
    }

    // Check whether the string has extra non-convertible characters in it.
    if (*end != '\0') {
        fprintf(stderr, "ERROR: Extra characters in '%s' at the end of input '%s'.\n", string, end);
        exit(EXIT_FAILURE);
    }

    return integer;
}

void validate_port(int port)
{
    // Check whether the port lies between the minimum and maximum allowed values.
    if (port < PORT_MIN_NUMBER || port > PORT_MAX_NUMBER) {
        fprintf(stderr, "ERROR: Port must be between %d and %d.\n", PORT_MIN_NUMBER, PORT_MAX_NUMBER);
        exit(EXIT_FAILURE);
    }
}