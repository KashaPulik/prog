#include <stdio.h>
#include "strings.h"

size_t my_strlen(char* str)
{
    size_t count = 0;
    while (*str != '\0') {
        count++;
        str++;
    }
    return count;
}

char* my_strcat(char* dest, char* src)
{
    char* tmp = dest + my_strlen(dest);
    for(char* i = src; *i != '\0'; i++) {
        *tmp = *i;
        tmp++;
    }
    *tmp = '\0';
    return dest;
}

char* my_strchr(char* s, int c)
{
    for (char* i = s; *i != '\0'; i++) {
        if (*i == c) {
            return i;
        }
    }
    return NULL;
}

int my_strcmp(char* str1, char* str2)
{
    char* tmp_str1 = str1;
    char* tmp_str2 = str2;
    while (*tmp_str1 == *tmp_str2) {
        if (*tmp_str1 == '\0')
            return 0;
        tmp_str1++;
        tmp_str2++;
    }
    if (*tmp_str1 > *tmp_str2)
        return 1;
    else
        return -1;
}

char* my_strcpy(char* toHere, char* fromHere)
{
    char* tmp = toHere;
    for (char* i = fromHere; *i != '\0'; i++) {
        *tmp = *i;
        tmp++;
    }
    *tmp = '\0';
    return toHere;
}

char* my_strstr(char* haystack, char* needle)
{
    char* tmp_haystack = haystack;
    char* tmp_needle = needle;
    char* buffer;
    while (1) {
        while (*tmp_haystack != *tmp_needle) {
            if (*tmp_haystack == '\0')
                return NULL;
            tmp_haystack++;
        }
        buffer = tmp_haystack;
        while (1) {
            tmp_haystack++;
            tmp_needle++;
            if (*tmp_needle == '\0') {
                return buffer;
            }
            if (*tmp_haystack != *tmp_needle)
                break;
        }
        tmp_haystack = buffer + 1;
        tmp_needle = needle;
    }
}

char* my_strtok(char* string, char delim)
{
    static char* last;
    if (string != NULL)
        last = string;
    if(last == NULL)
        return NULL;
    char* tmp = last;
    char* buffer = tmp;
    while (*tmp == delim)
        tmp++;
    if (*tmp == '\0')
        return NULL;
    buffer = tmp;
    while (*tmp != delim) {
        if (*tmp == '\0') {
            last = NULL;
            return buffer;
        }
        tmp++;
    }
    last = tmp + 1;
    *tmp = '\0';
    return buffer;
}

char* my_strpbrk(char* s, char* accept)
{
	for(int i = 0; s[i] != '\0'; i++)
		for(int j = 0; accept[j] != '\0'; j++)
			if(s[i] == accept[j])
				return &s[i];
	return NULL;
}

int my_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}

int my_tolower(int c)
{
    if(c >= 'A' && c <= 'Z')
        c += 'a' - 'A';
    return c;
}

int my_isalpha(int c)
{
    if (my_tolower(c) >= 'a' && my_tolower(c) <= 'z')
        return 1;
    return 0;
}

int my_atoi(char* str)
{
    char* tmp_str = str;
    int minus = 0;
    if(*tmp_str == '-') {
        minus = 1;
        tmp_str++;
    }
    if (!my_isdigit(*str))
        return 0;
    int number = *tmp_str - '0';
    tmp_str++;
    while (my_isdigit(*tmp_str)) {
        if(number > 999999999) {
            number = 2147483647;
            break;
        }
        number *= 10;
        number += *tmp_str - '0';
        tmp_str++;
    }
    if(minus)
        number = 0 - number;
    return number;
}
