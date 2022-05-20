#ifndef H_1
#define H_1
#include "internal/default.h"
void* v1_malloc(size_t v1_s);
void* v1_realloc(void (*v1_ptr), size_t v1_s);
void* v1_calloc(size_t v1_el_size, size_t v1_el_num);
void v1_free(void (*v1_ptr));
void* v1_malloc(size_t v1_s) {
	return (void*)(malloc(v1_s));
}

void* v1_realloc(void (*v1_ptr), size_t v1_s) {
	return (void*)(realloc(v1_ptr, v1_s));
}

void* v1_calloc(size_t v1_el_size, size_t v1_el_num) {
	return (void*)(calloc(v1_el_size, v1_el_num));
}

void v1_free(void (*v1_ptr)) {
	free(v1_ptr);
}


#endif
