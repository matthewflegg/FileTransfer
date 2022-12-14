#include "util/convert.h"
#include "util/file.h"
#include "util/socket.h"
#include <pthread.h>
#include <unistd.h>

#define ARGS_COUNT 4            // The number of command line arguments.
#define PORT_MAX_NUMBER 65535   // Highest port number the server can run on.
#define PORT_MIN_NUMBER 5000    // Lowest port number the server can run on.

/**
 * @brief  A thread function that saves a client's file name and contents.
 * @note   
 * @param  client_socket_pointer: A pointer to the client socket file descriptor.
 * @retval NULL
 */
void* handle_connection(void* client_socket_pointer);

/**
 * @brief  The main entry point of the application.
 * @note   
 * @param  argc: The number of command line arguments passed.
 * @param  argv: The command line arguments. Expected in the form ./[executable] <ip> <port> <queue length>.
 * @retval 0 on successful execution, -1 or none on failure.
 */
int main(int argc, char** argv)
{
    // Ensure the correct number of command line arguments have been passed.
    if (argc != ARGS_COUNT) {
        fprintf(stderr, "ERROR: Incorrect number of arguments (%d expected).\n", ARGS_COUNT);
        return EXIT_FAILURE;
    }

    // Assign command line arguments to their respective variables.
    char* ip = argv[1];
    int port = to_int(argv[2]);
    int queue_length = to_int(argv[3]);

    // Check whether the port lies between the minimum and maximum allowed values.
    if (port < PORT_MIN_NUMBER || port > PORT_MAX_NUMBER) {
        fprintf(stderr, "ERROR: Port must be between %d and %d.\n", PORT_MIN_NUMBER, PORT_MAX_NUMBER);
        return EXIT_FAILURE;
    }

    // Initialize the sockets by creating them, binding them and instructing them to listen.
    int server_socket = socket_create();
    socket_bind(server_socket, ip, port);
    socket_listen(server_socket, queue_length);

    // Iteratively fetch the file name & file contents from the client and save it.
    while (true) {

        // Wait for a connection before starting a new thread.
        struct sockaddr_in client_address;
        socklen_t address_size = sizeof client_address;
        int client_socket = socket_accept(server_socket, (struct sockaddr*)&client_address, &address_size);

        // After a connection has been made with the client, communicate with them in a non-blocking thread
        int* client_socket_pointer = malloc(sizeof client_socket);
        *client_socket_pointer = client_socket;
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_connection, client_socket_pointer);
    }
}

void* handle_connection(void* client_socket_pointer)
{
    char file_name[FILE_NAME_LENGTH_LIMIT];
    int client_socket = *((int*)client_socket_pointer);
    free(client_socket_pointer);
    client_socket_pointer = NULL;  // Prevents dangling pointer errors.

    // Handle the client connection accordingly by saving the file name and then the file contents.
    save_file_name(client_socket, file_name, FILE_NAME_LENGTH_LIMIT);
    save_file(client_socket, file_name);
    close(client_socket);
    return NULL;
}