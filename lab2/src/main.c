#include "IntVector.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    IntVector *a, *b;
    int i;
    a = int_vector_new(10);
    is_allright(a);

    int_vector_set_item(a, 0, 15);

    printf("a->data[0] = %d\n", int_vector_get_item(a, 0));

    b = int_vector_copy(a);
    is_allright(b);

    printf("%p - adress a, %p - adress b\n", a, b);
    printf("b->data[0] = %d\n", int_vector_get_item(b, 0));
    printf("Free vector b\n");
    int_vector_free(b);
    printf("Adress b - %p\n", b);
    printf("b->data[0] = %d\n", b->data[0]);
    printf("a->size = %ld\n", int_vector_get_size(a));
    printf("Let's init all vector a\n");
    for (i = 0; i < int_vector_get_capacity(a); i++) {
        int_vector_set_item(a, i, i);
    }
    for (i = 0; i < int_vector_get_capacity(a); i++) {
        printf("a->data[%d] = %d\n", i, int_vector_get_item(a, i));
    }
    printf("a->size = %ld\n", int_vector_get_size(a));
}