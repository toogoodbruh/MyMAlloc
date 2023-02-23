#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMSIZE  (4096/sizeof(size_t))

static size_t memory[MEMSIZE];

void *mymalloc(size_t size, char *file, int line){
    size_t *pMem = (size_t *)memory;
    size_t headerSize = 2; //header includes size and allocation indicator
    
    //initialize first chunk if not yet initialized
    if(pMem[0]==0){
        pMem[0] = MEMSIZE-headerSize; //size of first chunk is whole array minus header size
    }

    //calculate number of sizeof(size_t)-byte sets needed
    int sizeNum = size/sizeof(size_t);
    if(size % sizeof(size_t) != 0){
        sizeNum+=1;
    }

    //print error return null if size is zero or if size is bigger than total memory
    if(sizeNum==0){
        printf("Error in %s, line %d: Allocation of 0 bytes is not allowed.\n",file,line);
        return NULL;
    }
    else if(sizeNum>MEMSIZE){
        printf("Error in %s, line %d: Allocation is bigger than total memory.\n",file,line);
        return NULL;
    }

    //search for first open chunk
    size_t *c = pMem; //store chunk here

    //iterate through chunks in memory
    while(c < pMem + MEMSIZE){
        //if size chunk is big enough and it is not currently allocated, allocate chunk
        if(c[0]>=sizeNum && c[1]==0){
            c[1] = 1; //mark chunk as allocated

            //only split chunk if there is no room for a new header
            if(c[0]-sizeNum>=headerSize){
                c[headerSize+sizeNum] = c[0] - sizeNum - headerSize; //update size of next chunk
                c[0] = sizeNum; //update size of current chunk
            }
            return(c+headerSize); //return pointer to payload
        }
        //iterate to next chunk
        c = c + c[0] + headerSize;
    }
    printf("Error in %s, line %d: Not enough memory.\n",file,line);
    return NULL; //no available chunk found

}

void myfree(void *ptr, char *file, int line){
    size_t *pMem = (size_t *)memory;
    size_t headerSize = 2; //header includes size and allocation indicator
    
    //initialize first chunk if not yet initialized
    if(pMem[0]==0){
        pMem[0] = MEMSIZE-headerSize; //size of first chunk is whole array minus header size
    }

    //if pointer is not from array, return error
    if((size_t *)ptr<pMem || (size_t *)ptr>pMem+MEMSIZE){
        printf("Error in %s, line %d: Invalid address - this address is not from malloc().\n",file,line);
        return;
    }

    //search for matching chunk
    size_t *c = pMem; //store chunk iterator here

    //iterate through chunks in memory
    while(c < pMem + MEMSIZE){
        //if given pointer points to current chunk
        if(c+headerSize==ptr){
            //if chunk is allocated, de-allocate
            if(c[1]==1){
                c[1] = 0; //mark chunk as de-allocated
                return;
            }
            //otherwise, print error message and return
            else{
                printf("Error in %s, line %d: Memory already free.\n",file,line);
                return;
            }
        }
        //iterate to next chunk
        c = c + c[0] + headerSize;
    }
    //chunk not found - address is not from start of chunk
    printf("Error in %s, line %d: Invalid address - this address is not the start of a chunk.\n",file,line);
    return;
}