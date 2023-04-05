#include <stdio.h>

int main()
{
    FILE* file = fopen("bin/crash.bin", "wb");
    char numbers[6] = {0xf1, 0x80, 0x80, 0xe0, 0x80, 0x80};
    fwrite(numbers, 1, 6, file);
}