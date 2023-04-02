#include <error.h>

void error_output(
        const char* file_name, const char* function_name, const uint32_t line)
{
    printf("\x1b[31m"
           "Error"
           "\x1b[0m"
           " in file <%s>, function '%s', line: %d\n",
           file_name,
           function_name,
           line);
}