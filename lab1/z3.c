#include <stdio.h>

#define SQR(x) (x) * (x) // Макрофункция, возводящая во вторую степень

int main()
{
    int y = 5;
    int z = SQR(y + 1); // Вызов макрофункции
    printf("z = %d\n", z); // Вывод результата работы
    return 0;
}