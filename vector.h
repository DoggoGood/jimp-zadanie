#ifndef VECTOR_H
#define VECTOR_H

struct Vector {
    int *data;
    int size;
    int capacity;
};

void vector_push_back(struct Vector *v, int value);
void vector_free(struct Vector *v);

#endif
