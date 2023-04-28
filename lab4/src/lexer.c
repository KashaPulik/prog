#include <stdlib.h>

#include "./strings.h"
#include <lexer.h>

char* skip_spaces(char* str)
{
    while(*str == ' ')
        str++;
    return str;
}

int is_number(char* str)
{
    char* tmp_str = str;
    while (*tmp_str != '\0') {
        if (!my_isdigit(*tmp_str))
            return 0;
        tmp_str++;
    }
    return 1;
}

int check_end_symbol(char* str, char symbol)
{
    char* tmp_str = str;
    if (*(tmp_str + my_strlen(tmp_str) - 1) == symbol)
        return 1;
    return 0;
}

int check_ip(char* str)
{
    char* tmp_str = malloc(my_strlen(str) + 1);
    char* buffer = tmp_str;
    if (!check_end_symbol(str, ':')) {
        free(buffer);
        return 0;
    }
    tmp_str = my_strcpy(tmp_str, str);
    tmp_str = skip_spaces(tmp_str);
    *(tmp_str + my_strlen(tmp_str) - 1) = '\0';
    int count = 0;
    char* token;
    char* tokens[16];
    tokens[0] = my_strtok(tmp_str, '.');
    while (tokens[count] != NULL) {
        count++;
        tokens[count] = my_strtok(NULL, '.');
    }
    if (count != 4) {
        free(buffer);
        return 0;
    }
    for (count = 0; count < 4; count++) {
        token = tokens[count];
        if (!is_number(token)) {
            free(buffer);
            return 0;
        }
        if (my_atoi(token) > 255 || my_atoi(token) < 0) {
            free(buffer);
            return 0;
        }
    }
    free(buffer);
    return 1;
}

int check_upper_domens(char* str)
{
    if (!(my_strcmp(str, "ru") && my_strcmp(str, "com")
          && my_strcmp(str, "org")))
        return 1;
    return 0;
}

int is_word(char* str)
{
    char* tmp_str = str;
    while (*tmp_str != '\0') {
        if (!my_isalpha(*tmp_str))
            return 0;
        tmp_str++;
    }
    return 1;
}

int check_domen(char* str)
{
    char* tmp_str = malloc(my_strlen(str) + 1);
    char* buffer = tmp_str;
    if (!check_end_symbol(str, ':')) {
        free(buffer);
        return 0;
    }
    tmp_str = my_strcpy(tmp_str, str);
    tmp_str = skip_spaces(tmp_str);
    *(tmp_str + my_strlen(tmp_str) - 1) = '\0';
    int count = 0;
    char* token;
    char* tokens[16];
    tokens[0] = my_strtok(tmp_str, '.');
    while (tokens[count] != NULL) {
        count++;
        if (count > 4) {
            free(buffer);
            return 0;
        }
        tokens[count] = my_strtok(NULL, '.');
    }
    if (count < 2) {
        free(buffer);
        return 0;
    }
    if (!check_upper_domens(tokens[count - 1]))
        return 0;
    for (int i = 0; i < count; i++) {
        token = tokens[i];
        if (!is_word(token)) {
            free(buffer);
            return 0;
        }
    }
    free(buffer);
    return 1;
}

int check_path_symbols(char* str, char* wrong_symbol)
{
    if (my_strpbrk(str, wrong_symbol) == NULL)
        return 1;
    return 0;
}

int check(char* str)
{
    if(my_strlen(str) > MAX_PATH)
        return OVER_MAX_LEN;
    if (check_path_symbols(str, "\\*?«<>|") == 0)
        return ILLEGAL_CHARACTER;
    char tmp_str[my_strlen(str) + 1];
    my_strcpy(tmp_str, str);
    my_strtok(tmp_str, '/');
    if (my_isdigit(tmp_str[0]) && check_ip(tmp_str))
            return SUCCESS;
    else if (my_isalpha(tmp_str[0]) && check_domen(tmp_str))
            return SUCCESS;
    
    return WRONG_IP_DOMEN;
}

char* convert_path(char* path)
{
	int path_len = my_strlen(path);
    char* new_path = malloc(path_len + 2);
    char* buffer = new_path;
    char path_copy[path_len + 1];
    my_strcpy(path_copy, path);
    char* tokens[16];
    int count = 0;
    tokens[count] = my_strtok(path_copy, '/');
    int ip_len = my_strlen(tokens[count]);
    tokens[count][ip_len - 1] = '\0';
    while (tokens[count] != NULL) {
        count++;
        tokens[count] = my_strtok(NULL, '/');
    }
    buffer[0] = '\\';
    buffer[1] = '\\';
    buffer[2] = '\0';
    buffer += 2;
    int i;
    for (i = 0; i < count - 1; i++) {
        buffer = my_strcat(buffer, tokens[i]);
        buffer += my_strlen(tokens[i]);
        *buffer = '\\';
        buffer++;
    }
    buffer = my_strcat(buffer, tokens[i]);
    if (check_end_symbol(path, '/')) {
        buffer += my_strlen(tokens[i]);
        *buffer = '\\';
        buffer++;
        *buffer = '\0';
    }
    return new_path;
}

char* process(char** tokens, char delim)
{
    char* new_paths = malloc(2048);
    char* buffer = new_paths;
    char* new_path;
    while(*tokens != NULL) {
        if(**tokens == '\0') {
            tokens++;
            continue;
        }
        new_path = convert_path(*tokens);
        buffer = my_strcat(buffer, new_path);
        buffer += my_strlen(buffer);
        *buffer = delim;
        buffer++;
        tokens++;
        free(new_path);
    }
    buffer--;
    *buffer = '\0';
    return new_paths;
}
