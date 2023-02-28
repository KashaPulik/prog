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
		free(vector);
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
	copy->data = (int*) malloc(v->capacity * sizeof(int));
	if(!copy->data) {
		free(copy);
		return NULL;
	}
	copy->size = v->size;
	copy->capacity = v->capacity;
	for(int i = 0; i < v->size; i++) {
		copy->data[i] = v->data;
	}
	return copy;
}

void int_vector_free(IntVector *v)
{
	free(v->data);
	free(v);
}

int int_vector_get_item(const IntVector *v, size_t index)
{
	return v->data[index];
}

void int_vector_set_item(IntVector *v, size_t index, int item)
{
	v->data[index] = item;
}

size_t int_vector_get_size(const IntVector *v)
{
	return v->size;
}

size_t int_vector_get_capacity(const IntVector *v)
{
	return v->capacity;
}

int int_vector_push_back(IntVector *v, int item)
{
	int* tmp;
	if(v->size == v->capacity) {
		tmp = (int) realloc(v->data, v->capacity * 2);
		if(!tmp) {
			return -1;
		}
		v->data = tmp;
		v->capacity *= 2;
	}
	v->data[v->size - 1] = item;
	v->size++;
	return 0;
}

void int_vector_pop_back(IntVector *v)
{
	if(v->size > 0) {
		v->size--;
	}
}

int int_vector_shrink_to_fit(IntVector *v)
{
	v->capacity = v->size;
}

int int_vector_resize(IntVector *v, size_t new_size)
{
	int *tmp;
	if(v->size == new_size) {
		return -1;
	}
	if(new_size < v->size) {
		v->capacity = int_vector_shrink_to_fit(v);
		return 0;
	}
	if(new_size > v->capacity) {
		tmp = (int) realloc(v->data, new_size);
		if(!tmp)
			return -1;
		v->data = tmp;
	}
	for(int i = v->size; i < new_size; i++) {
		v->data[i] = 0;
	}
	return 0;
}

int int_vector_reserve(IntVector *v, size_t new_capacity)
{
	int *tmp;
	if(new_capacity <= v->capacity)
		return -1;
	tmp = (int) realloc(v->data, new_capacity);
	if(!tmp)
		return -1;
	v->data = tmp;
	v->capacity = new_capacity;
	return 0;
}