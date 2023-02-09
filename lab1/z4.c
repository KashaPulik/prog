#include <stdio.h>
void swap(int *a, int *b) // Функции, которая меняет элементы местами

{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(int *array, int size) // Пузырьковая сортировка
{
    int i, j;
    for (i = 0; i < size - 1; ++i) { // Внешний цикл, совершающий size - 1 итераций
        for (j = 0; j < size - i - 1; ++j) {
            if (array[j] > array[j + 1]) {// Если текущий элемент больше следующего, то
                swap(&array[j], &array[j + 1]); // Поменять элементы местами
            }
        }
    }
}

int main()
{
    int array[100] = {10, 15, 5, 4, 21, 7}; // Объявление и инициализация массива

    bubble_sort(array, 6); // Вызов функции для сортировки массива

    int i;
    for (i = 0; i < 6; ++i)
    {
        printf("%d ", array[i]); // Вывод значений результирующего массива
    }
    printf("\n");

    return 0;
}