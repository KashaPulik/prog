#include <stdio.h>

int main()
{
    FILE* file = fopen("crash.bin", "wb");
    char numbers[5] = {0xff, 0x1f, 0xe2, 0x84, 0x7f};
    fwrite(numbers, 1, 5, file);
}