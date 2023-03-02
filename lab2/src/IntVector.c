#include <stdlib.h>
#include <stdio.h>

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
	IntVector *copy = (IntVector*) malloc(sizeof(IntVector));
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
		copy->data[i] = v->data[i];
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
	if(index == v->size)
		v->size = index + 1;
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
		tmp = (int*) realloc(v->data, v->capacity * sizeof(int) * 2);
		if(!tmp) {
			return -1;
		}
		v->data = tmp;
		v->capacity *= 2;
	}
	v->data[v->size] = item;
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
	if(!v->size)
		return -1;
	int *tmp;
	if(v->capacity > v->size) {
		tmp = (int*) realloc(v->data, v->size * sizeof(int));
		if(!tmp)
			return -1;
		v->data = tmp;
		v->capacity = v->size;
		return 0;
	}
	return -1;
}

int int_vector_resize(IntVector *v, size_t new_size)
{
	int *tmp;
	if(v->size == new_size) {
		return -1;
	}
	if(new_size > v->capacity) {
		tmp = (int*) realloc(v->data, new_size * sizeof(int));
		if(!tmp)
			return -1;
		v->data = tmp;
		v->capacity = new_size;
	}
	for(int i = v->size; i < new_size; i++) {
		v->data[i] = 0;
	}
	v->size = new_size;
	return 0;
}

int int_vector_reserve(IntVector *v, size_t new_capacity)
{
	int *tmp;
	if(new_capacity <= v->capacity)
		return -1;
	tmp = (int*) realloc(v->data, new_capacity * sizeof(int));
	if(!tmp)
		return -1;
	v->data = tmp;
	v->capacity = new_capacity;
	return 0;
}

void is_allright(IntVector *v)
{
	if(!v){
		printf("\x1b[31m" "Error" "\x1b[0m" ": can't allocate memory\n");
		exit(1);
	}
}