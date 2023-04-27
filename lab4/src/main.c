#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "strings.h"
#include "interface.h"

int main()
{
    char delim;
    char* paths = input(&delim);
    char* new_paths;
    char* tokens[32];
    int count = 0;
    tokens[count] = my_strtok(paths, delim);
    while (tokens[count] != NULL) {
        count++;
        tokens[count] = my_strtok(NULL, delim);
    }
    for(int i = 0; i < count; i++) {
        if(check(tokens[i]))
            *tokens[i] = '\0';
    }
    new_paths = process(&tokens[0], delim);
    output(new_paths);
    free(paths);
    free(new_paths);
}