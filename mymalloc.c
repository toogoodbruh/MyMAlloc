#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMSIZE  4096

static char memory[MEMSIZE];

void *mymalloc(size_t size, char *file, int line){
    size_t *pMem = (size_t *)memory; //use pMem to write numbers in memory
    size_t headerSize = sizeof(size_t) + sizeof(char); //header includes size of chunk (short) and allocation status (char)
    
    //initialize first chunk if not yet initialized
    if(pMem[0]==0){
        pMem[0] = MEMSIZE-headerSize; //size of first chunk is whole array minus header size
    }
    
    printf("%d",pMem[0]); //test
}

void myfree(void *ptr, char *file, int line){
    size_t *pMem = (size_t *)memory; //use pMem to write numbers in memory
    size_t headerSize = sizeof(size_t) + sizeof(char); //header includes size of chunk (short) and allocation status (char)
    
    //initialize first chunk if not yet initialized
    if(pMem[0]==0){
        pMem[0] = MEMSIZE-headerSize; //size of first chunk is whole array minus header size
    }

}