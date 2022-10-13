#include "auth.h"

char* get_user_password_input()
{
    // Get settings of the terminal currently displayed
    static struct termios new_terminal, old_terminal;
    tcgetattr(STDIN_FILENO, &old_terminal);

    // Do not echo the characters typed in
    new_terminal = old_terminal;
    new_terminal.c_lflag &= ~(ECHO);

    // Set the options specified above as the new terminal options
    tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal);

    char* password = malloc(MAX_PASSWORD_LENGTH);
    printf("ENTER A PASSWORD: ");
    
    if (fgets(password, MAX_PASSWORD_LENGTH, stdin) == NULL) {
        fprintf(stderr, "ERROR: Could not read password.\n");
        exit(EXIT_FAILURE);
    }

    size_t password_length = strlen(password);

    if (password[password_length - 1] == '\n') {
        password[password_length - 1] = '\0';
    }

    char* salt = crypt_gensalt("$2b$", 15, NULL, 0);
    char* encrypted = crypt(password, salt);
    return encrypted;
}

void send_password_hash(int client_socket, char password_hash[MAX_PASSWORD_LENGTH])
{
    if (send(client_socket, password_hash, MAX_PASSWORD_LENGTH, 0) < 0) {
        fprintf(stderr, "ERROR: Could not send the password hash to the specfied socket.\n");
        exit(EXIT_FAILURE);
    }
}

void receive_password_hash(int client_socket, char password_hash_out_param[MAX_PASSWORD_LENGTH])
{
    if (recv(client_socket, password_hash_out_param, MAX_PASSWORD_LENGTH, 0) < 0) {
        fprintf(stderr, "ERROR: Could not receive password hash.\n");
        exit(EXIT_FAILURE);
    }
}

void overwrite_password_if_none_set(char password_hash[MAX_PASSWORD_LENGTH])
{
    FILE* password_file;

    // Overwrite the contents of the password file with the new hash if not set.
    if (total_chars_in_file(PASSWORD_FILE_NAME) > 0) {
        return;
    }

    if ((password_file = fopen(PASSWORD_FILE_NAME, "w")) == NULL) {
        fprintf(stderr, "ERROR: Failed to open the password file %s.\n", PASSWORD_FILE_NAME);
        exit(EXIT_FAILURE);
    }

    printf("INFO: No password has been set. Overwriting...\n");
    fprintf(password_file, password_hash);
    fclose(password_file);
}   

bool validate_password(char password_hash[MAX_PASSWORD_LENGTH])
{
    FILE* password_file;

    if ((password_file = fopen(PASSWORD_FILE_NAME, "r")) == NULL) {
        fprintf(stderr, "ERROR: Could not open the password file %s for reading.\n", PASSWORD_FILE_NAME);
        exit(EXIT_FAILURE);
    }

    char password_hash_expected[MAX_PASSWORD_LENGTH];

    if (fgets(password_hash_expected, MAX_PASSWORD_LENGTH, password_file) == NULL) {
        fprintf(stderr, "ERROR: Could not read the password file.\n");
        fclose(password_file);
        exit(EXIT_FAILURE);
    }

    if (strcmp(password_hash, password_hash_expected) == 0) {
        fclose(password_file);
        return true;  // Password is correct.
    }

    fclose(password_file);
    return false;  // Password is incorrect.
}