#include <stdio.h>

typedef struct
{
    char str[8]; // Поле структуры типа char из восьми символов
    int num; // Поле, хранящее целочисленное значение
} NumberRepr;

void format(NumberRepr *number)
{
    sprintf(number->str, "%3d", number->num); // Вывод в строку str
}

int main()
{
    NumberRepr number = {.num = 1025}; // Объявление переменной типа структуры

    format(&number); // Вызов функции формат

    printf("str: %s\n", number.str); // Вывод строкового поля
    printf("num: %d\n", number.num); // Вывод целочисленного поля

    return 0;
}