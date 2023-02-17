#include <stdlib.h>

typedef struct {
	size_t size;
	size_t capacity;
	int* data;
} IntVector;

IntVector *int_vector_new(size_t initial_capacity)
{
	IntVector *vector = (IntVector*) malloc(sizeof(IntVector));
	if(!vector) {
		return NULL;
	}
	
	vector->data = (int*) malloc(initial_capacity * sizeof(int));
	if(!vector->data) {
		free(vector)
		return NULL;
	}
	vector->capacity = initial_capacity;
	vector->size = 0;
	return vector;
}

IntVector *int_vector_copy(const IntVector *v)
{
	IntVector *copy = (IntVector*) malloc(sizeof(v));
	if(!copy) {
		return NULL;
	}
	copy
}
