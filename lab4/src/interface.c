#include <stdio.h>
#include <stdlib.h>

char* input(char* delim)
{
    char* paths = malloc(1024);
    printf("delim: ");
    scanf("%c", delim);
    printf("paths: ");
    scanf("%s", paths);
    return paths;
}

void output(char* new_paths)
{
    printf("new paths: %s\n", new_paths);
}