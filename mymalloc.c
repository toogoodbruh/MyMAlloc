#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMSIZE  4096

static char memory[MEMSIZE];

void *mymalloc(size_t size, char *file, int line){
    unsigned short *shortMem = (unsigned short *)memory; //use shortMem to write shorts in memory
    unsigned char headerSize = sizeof(short) + sizeof(char); //header includes size of chunk (short) and allocation status (char)
    
    //initialize first chunk if not yet initialized
    if(shortMem[0]==0){
        shortMem[0] = MEMSIZE-headerSize; //size of first chunk is whole array minus header size
    }
    
    printf("%d\n",shortMem[0]); //test initialization
}

void myfree(void *ptr, char *file, int line){
    unsigned short *shortMem = (unsigned short *)memory; //use shortMem to write shorts in memory
    unsigned char headerSize = sizeof(short) + sizeof(char); //header includes size of chunk (short) and allocation status (char)
    
    //initialize first chunk if not yet initialized
    if(shortMem[0]==0){
        shortMem[0] = MEMSIZE-headerSize; //size of first chunk is whole array minus header size
    }

}