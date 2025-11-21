#include <stdlib.h>
#include "vector.h"

void vector_push_back(struct Vector *v, int value) {
    if (v->size >= v->capacity) {
        v->capacity = v->capacity == 0 ? 1 : v->capacity * 2;
        v->data = realloc(v->data, v->capacity * sizeof(int));
    }
    v->data[v->size++] = value;
}

void vector_free(struct Vector *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}
