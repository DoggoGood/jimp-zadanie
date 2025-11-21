#include "skorowidz.h"
#include "vector.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 8192 // zakładamy, że linie będą krótsze niż 8kB

int occurance_count_cmp(const void *a, const void *b) {
    struct skorowizd *sa = (struct skorowizd *)a;
    struct skorowizd *sb = (struct skorowizd *)b;
    return sa->occurance_count - sb->occurance_count;
}

int contains_word(char *line, char *word) {
    char *pos = line;
    int word_len = strlen(word);
    while ((pos = strstr(pos, word)) != NULL) {
        if ((pos == line || !isalpha(*(pos - 1))) &&
            (pos[word_len] == '\0' || !isalpha(pos[word_len]))) {
            return 1;
        }
        pos += word_len;
    }
    return 0;
}

int main(int argc, char **argv) {
    int i, j;
    int ile_linii;
    int ile_slow = 0;
    char buf[BUFSIZE];

    FILE *in = argc > 1 ? fopen(argv[1], "r") : stdin;
    struct skorowizd *t = calloc(argc - 2, sizeof(struct skorowizd));
    for (i = 2; i < argc; i++) {
        t[ile_slow].word = argv[i];
        t[ile_slow].lines = malloc(sizeof(struct Vector));
        t[ile_slow].lines->data = NULL;
        t[ile_slow].lines->size = 0;
        t[ile_slow].lines->capacity = 0;
        ile_slow++;
    }

    if (ile_slow == 0) {
        fprintf(stderr, "%s: błąd: proszę podać słowa do wyszukiwania\n",
                argv[0]);
        free(t);
        return EXIT_FAILURE;
    }

    if (in == NULL) {
        fprintf(stderr, "%s: błąd: nie mogę czytać pliku %s\n", argv[0],
                argv[1]);
        for (i = 0; i < ile_slow; i++) {
            skorowidz_free(&t[i]);
        }
        free(t);
        return EXIT_FAILURE;
    }

    ile_linii = 0;
    while (fgets(buf, BUFSIZE, in) != NULL) {
        ile_linii++;
        for (i = 0; i < ile_slow; i++) {
            if (contains_word(buf, t[i].word) == 1) {
                t[i].occurance_count++;
                vector_push_back(t[i].lines, ile_linii);
            }
        }
    }

    qsort(t, ile_slow, sizeof(struct skorowizd), occurance_count_cmp);

    for (i = 0; i < ile_slow; i++) {
        if (t[i].occurance_count > 0) {
            printf("słowo \"%s\" wystąpiło w liniach:", t[i].word);
            for (j = 0; j < t[i].lines->size; j++)
                printf(" %d", t[i].lines->data[j]);
            printf("\n");
        } else {
            printf("nie napotkano słowa \"%s\"\n", t[i].word);
        }
    }
    for (i = 0; i < ile_slow; i++) {
        skorowidz_free(&t[i]);
    }
    free(t);
    if (in != stdin) {
        fclose(in);
    }
    return EXIT_SUCCESS;
}
