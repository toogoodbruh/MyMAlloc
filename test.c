#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

void printA(size_t *p){
    //iterate through chunks in memory
    size_t *pMem = p;
    while(p < pMem + (4096/sizeof(size_t))){
        printf("\n\nSize: %d\nAllocation Status: %d\nAddress: %d",p[0]*4,p[1],p);
        //iterate to next chunk
        p = p + p[0] + 2;
    }
}

int main(int argc, char **argv)
{
    size_t *p = malloc(200);
    //size_t *a = malloc(5000); //test bigger chunk than mem
    size_t *a = malloc(50);
    size_t *q = malloc(10);
    size_t *b = malloc(2950);
    //malloc(0);
    size_t *c = malloc(801);
    free(a);
    free(b);
    free(q);
    //size_t *z = malloc(60);
    //size_t *y = malloc(5);
    //free(q); //test repeated freeing
    //free(q+1); //test freeing non chunk address
    //free(&q); //test freeing outside of mem address
    //malloc(101);
    printA(p-2);

    return EXIT_SUCCESS;
}