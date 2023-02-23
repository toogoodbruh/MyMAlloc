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
    free(p);
    free(p);
    //size_t *z = malloc(60);
    //size_t *y = malloc(5);
    //free(q); //test repeated freeing
    //free(q+1); //test freeing non chunk address
    //free(&q); //test freeing outside of mem address
    //malloc(101);
    printA(p-2);

    //try to allocate 0
    //try to allocate bigger than memory
    //randomly fill array with 49 chunks of size 10 up to size 64
    //try to make chunk bigger than remaining chunk
    //try to allocate 0
    //then make a final chunk filling the rest of the array
    //try to allocate 0
    //try to allocate bigger than memory
    //prove no chunks overlap, all addresses are divisible by 4, and that no chunks go outside allocated memory
    //above also proves part 6
    //free just 1 char outside memory on both sides of memory
    //try to free addresses outside of chunks
    //then free first chunk, last chunk and any middle chunk; save sizes
    //free just 1 char outside memory on both sides of memory
    //try to free addresses outside of chunks
    //reallocate chunks in 2 half size chunks (unless they are size 1, then reallocate as itself)
    //free memory in random order
    //free twice each time to show that error checking works
    //between each free, check that no adjacent chunks are unallocated, proper chunk is unallocated
    //this proves that allocation was proper in first place
    //every 5 chunks freed, allocate new memory of size 3 in new array
    //free entire array except one
    //allocate a chunk for one third of memory size
    //free last one and last chunk
    //allocate a chunk for whole memory
    //free
    //start over without reinitializing, repeat 10 times

    //also note - finish memgrind 4 & 5 (& clean)

    return EXIT_SUCCESS;
}