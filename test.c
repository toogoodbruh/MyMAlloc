#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main(int argc, char **argv)
{
    malloc(200);
    malloc(5000);
    size_t *p = malloc(10);
    size_t *f = malloc(3000);
    malloc(0);
    malloc(801);
    free(p);
    free(p);
    free(p+1);
    free(&p);
    malloc(101);
    return EXIT_SUCCESS;
}
