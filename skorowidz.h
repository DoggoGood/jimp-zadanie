#ifndef SKOROWIDZ_H
#define SKOROWIDZ_H

#include "vector.h"

struct skorowizd {
    char *word;
    int occurance_count;
    struct Vector *lines;
};

void skorowidz_free(struct skorowizd *s);

#endif
