#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMSIZE  4096

static char memory[MEMSIZE];

void *mymalloc(size_t size, char *file, int line){
    size_t *pMem = (size_t *)memory; //use pMem to read & write sizes in memory
    size_t headerSize = sizeof(size_t) + sizeof(char); //header includes size of chunk (short) and allocation status (char)
    
    //initialize first chunk if not yet initialized
    if(pMem[0]==0){
        pMem[0] = MEMSIZE-headerSize; //size of first chunk is whole array minus header size
    }

    //search for first open chunk
    size_t *c = pMem; //store chunk here

    //iterate through chunks in memory
    while(c < pMem + MEMSIZE){
        //if size chunk is big enough and it is not currently allocated, allocate chunk
        if(c[0]>=size && (char *)c[headerSize-1]==0){
            ((char *)c)[headerSize-1] = 1; //mark chunk as allocated

            //only split chunk if there is no room for a new header
            if(c[0]-size>=headerSize){
                c[size+headerSize] = c[0] - size - headerSize; //update size of next chunk
                c[0] = size; //update size of current chunk
            }

            return(c+headerSize); //return pointer to payload
        }
        //iterate to next chunk
        c = c + c[0] + headerSize;
    }
    
    return NULL; //no available chunk found

}

void myfree(void *ptr, char *file, int line){
    size_t *pMem = (size_t *)memory; //use pMem to write numbers in memory
    size_t headerSize = sizeof(size_t) + sizeof(char); //header includes size of chunk (short) and allocation status (char)
    
    //initialize first chunk if not yet initialized
    if(pMem[0]==0){
        pMem[0] = MEMSIZE-headerSize; //size of first chunk is whole array minus header size
    }

}