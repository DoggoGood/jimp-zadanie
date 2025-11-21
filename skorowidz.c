#include <stdlib.h>
#include "skorowidz.h"

void skorowidz_free(struct skorowizd *s) {
    vector_free(s->lines);
    free(s->lines);
}
