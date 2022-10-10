#include "convert.h"

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