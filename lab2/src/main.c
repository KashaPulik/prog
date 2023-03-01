#include "IntVector.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    IntVector *a, *b;
    int i, check;

    printf("Create vector a\n");
    a = int_vector_new(10);
    is_allright(a);

    printf("Set 0 item of vector a to value 15\n");
    int_vector_set_item(a, 0, 15);
    printf("a->data[0] = %d\n", int_vector_get_item(a, 0));
    printf("\n");

    printf("Create vector b - copy of vector a\n");
    b = int_vector_copy(a);
    is_allright(b);
    printf("%p - adress a, %p - adress b\n", a, b);
    printf("b->data[0] = %d\n", int_vector_get_item(b, 0));
    printf("Free vector b\n");
    int_vector_free(b);
    printf("Adress b - %p\n", b);
    printf("b->data[0] = %d\n", int_vector_get_item(b, 0));
    printf("\n");

    printf("a->size = %ld\n", int_vector_get_size(a));
    printf("Let's init entire vector a\n");
    for (i = 0; i < int_vector_get_capacity(a); i++) {
        int_vector_set_item(a, i, i);
    }
    for (i = 0; i < int_vector_get_capacity(a); i++) {
        printf("a->data[%d] = %d\n", i, int_vector_get_item(a, i));
    }
    printf("a->size = %ld\n", int_vector_get_size(a));
    printf("a->capacity = %ld\n", int_vector_get_capacity(a));
    printf("\n");

    printf("Let's push another element to vector a\n");
    check = int_vector_push_back(a, 10);
    if (check) {
        printf("\x1b[31m"
               "Error\n"
               "\x1b[0m");
        exit(1);
    }
    printf("a->data[10] = %d\n", int_vector_get_item(a, 10));
    printf("a->size = %ld\n", int_vector_get_size(a));
    printf("a->capacity = %ld\n", int_vector_get_capacity(a));
    printf("\n");

    printf("Delete last element from vector a\n");
    printf("And shrink to fit vector a\n");
    int_vector_pop_back(a);
    int_vector_shrink_to_fit(a);
    printf("a->size = %ld\n", int_vector_get_size(a));
    printf("a->capacity = %ld\n", int_vector_get_capacity(a));
    printf("\n");

    printf("Now resize vector a and check its elements\n");
    int_vector_resize(a, 15);
    printf("a->size = %ld\n", int_vector_get_size(a));
    printf("a->capacity = %ld\n", int_vector_get_capacity(a));
    for (i = 0; i < int_vector_get_capacity(a); i++) {
        printf("a->data[%d] = %d\n", i, int_vector_get_item(a, i));
    }
    printf("\n");

    printf("Let's try to change capacity of vector a\n");
    int_vector_reserve(a, 17);
    printf("a->capacity = %ld\n", int_vector_get_capacity(a));
    printf("\n");

    printf("Now test some boundary cases\n");
    printf("a->size = %ld\n", int_vector_get_size(a));
    printf("a->data[0] = %d\n", int_vector_get_item(a, 0));
    int_vector_resize(a, 0);
    printf("int_vector_resize(a, 0)\n");
    printf("a->size = %ld\n", int_vector_get_size(a));
    int_vector_push_back(a, 10);
    printf("int_vector_push_back(a, 10)\n");
    printf("a->data[0] = %d\n", int_vector_get_item(a, 0));
    printf("\n");

    printf("Finally, free vector a\n");
    int_vector_free(a);
    printf("a->data[0] = %d\n", int_vector_get_item(a, 0));
}