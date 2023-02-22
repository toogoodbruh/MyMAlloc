#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMSIZE  4096

static char memory[MEMSIZE];

void *mymalloc(size_t size, char *file, int line){
    int *p = (int *)memory; //use p to write in memory with integers
    if(p[0]==0){
        p[0] = MEMSIZE-sizeof(int *)-1; //size of first chunk is whole array minus header size
        //figure out how to write 0 and 1 (not allocated vs allocated) here
    }
    printf("%d\n",p[0]); //test initialization
}

void myfree(void *ptr, char *file, int line){

}