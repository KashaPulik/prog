#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

size_t encode_varint(uint32_t value, uint8_t* buf)
{
    assert(buf != NULL);
    uint8_t* cur = buf;
    while (value >= 0x80) {
        const uint8_t byte = (value & 0x7f) | 0x80;
        *cur = byte;
        value >>= 7;
        ++cur;
    }
    *cur = value;
    ++cur;
    return cur - buf;
}

uint32_t decode_varint(const uint8_t** bufp)
{
    const uint8_t* cur = *bufp;
    uint8_t byte = *cur++;
    uint32_t value = byte & 0x7f;
    size_t shift = 7;
    while (byte >= 0x80) {
        byte = *cur++;
        value += (byte & 0x7f) << shift;
        shift += 7;
    }
    *bufp = cur;
    return value;
}

uint32_t generate_number()
{
    const int r = rand();
    const int p = r % 100;
    if (p < 90) {
        return r % 128;
    }
    if (p < 95) {
        return r % 16384;
    }
    if (p < 99) {
        return r % 2097152;
    }
    return r % 268435455;
}

int main()
{
	FILE* uncompressed = fopen("uncompressed.dat", "wb");
	FILE* compressed = fopen("compressed.dat", "wb");
	uint32_t number, i;
	uint32_t decode_number;
	uint8_t buf[4];
	uint8_t* bufer = malloc(4000000);
	const uint8_t* point = bufer;
	uint32_t buf_size;
	double comp_size = 0, uncomp_size = 0;
	
	for(i = 0; i < 1000000; i++) {
		number = generate_number();
		fwrite(&number, 4, 1, uncompressed);
		buf_size = encode_varint(number, buf);
		fwrite(buf, 1, buf_size, compressed);
		comp_size += buf_size;
		uncomp_size += 4;
	}
	printf("Коэффициент сжатия = %.1f\n", (uncomp_size/comp_size));
	
	fclose(uncompressed);
	fclose(compressed);
	
	uncompressed = fopen("uncompressed.dat", "rb");
	compressed = fopen("compressed.dat", "rb");
	
	
	fread(bufer, 1, 4000000, compressed);
	i = 0;
	
	for(i = 0; i < 1000000; i++) {
		fread(&number, 4, 1, uncompressed);
		decode_number = decode_varint(&point);
		if(number != decode_number) {
			printf("%d Кодирование прошло безуспешно\n", i);
			return 1;
		}
	}
	printf("Успех!\n");
}
