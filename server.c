#include "util/file.h"
#include "util/socket.h"
#include <string.h>

#define ARGS_COUNT 4
#define PORT_MAX_NUMBER 65535
#define PORT_MIN_NUMBER 5000

/**
 * @brief  Convert a string to an integer. Includes internal error checking.
 * @note   
 * @param  string: The string to convert to and integer.
 * @retval The string converted to an integer.
 */
int string_to_int(const char* string);

/**
 * @brief  Check if a port number lies between PORT_MIN_NUMBER and PORT_MAX_NUMBER.
 * @note   
 * @param  port: The port to validate.
 * @retval None
 */
void validate_port(int port);

int main(int argc, char** argv)
{
    // Declare variables to be used later.
    int metadata_socket, file_socket;
    int metadata_port, file_port;
    char* ip;

    // Check whether the correct number of command line arguments were passed.
    if (argc != ARGS_COUNT) {
        fprintf(stderr, "ERROR: Invalid number of arguments (%d required).\n", ARGS_COUNT);
        exit(EXIT_FAILURE);
    }

    // Assign `ip` and the `*_port` variables values if they are valid.
    ip = argv[1];
    validate_port(metadata_port = string_to_int(argv[2]));
    validate_port(file_port = string_to_int(argv[3]));

    // char* ptr;
    // metadata_port = (int)strtol(argv[2], &ptr, 10);
    // file_port = (int)strtol(argv[3], &ptr, 10);
}

int string_to_int(const char* string)
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