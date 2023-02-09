#include <stdio.h>
#include <stdlib.h>

void init(int **arr, int n)
{
    *arr = malloc(n * sizeof(int)); // Выделение памяти для массива
    int i;
    for (i = 0; i < n; ++i) // Проход по массиву
    {
        *(*arr + i) = i; // Арифметика указателей
    }
}

int main()
{
    int *arr = NULL;
    int n = 10; // Объявление и инициализация переменной для размера массива
    init(&arr, n); // Вызов функции для инициализации массива

    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%d\n", arr[i]); // Вывод значений массива
    }
    return 0;
}