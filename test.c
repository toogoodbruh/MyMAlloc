#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMSIZE     4096
#define HEADSIZE    8
#define ALIGNMENT   4

void printA(size_t *p){
    //iterate through chunks in memory
    size_t *pMem = p;
    while(p < pMem + (4096/sizeof(size_t))){
        printf("\n\nSize: %d\nAllocation Status: %d\nAddress: %d",p[0]*4,p[1],p);
        //iterate to next chunk
        p = p + p[0] + 2;
    }
}

void printB(char *p){
    //iterate through chunks in memory
    char *pMem = p;
    int count = 1;
    int size = 0;
    while(p < pMem + MEMSIZE && count<75){
        if(p[ALIGNMENT]==1){
            size+=p[0]*ALIGNMENT;
        }
        printf("\n\n%d\nSize: %d\nAllocation Status: %d\nAddress: %d",count,p[0]*ALIGNMENT,p[ALIGNMENT],p);
        //iterate to next chunk
        p = p + HEADSIZE + p[0]*ALIGNMENT;
        count++;
    }
    printf("\n\nSize: %d",size+HEADSIZE*50);
}

void printC(char *p[], int size){
    printf("hi");
    for(int i = 0; i<size; i++){
        char *q = p[i]-HEADSIZE;
        printf("\n\n%d\nSize: %d\nAllocation Status: %d\nAddress: %d",i+1,q[0]*ALIGNMENT,q[ALIGNMENT],q);
    }
}

int allocateZero(){
    //try to allocate a chunk of 0 bytes
    char *p = malloc(0); //should produce error message, test.c line 21
    if(p!=NULL){
        return 1;
    }
    return 0;
}

int allocateLargeMemory(){
    int errors = 0;

    //try to allocate more memory than total memory
    char *p = malloc(MEMSIZE+1); //should produce error message, test.c line 32
    if(p!=NULL){
        errors+=1;
    }
    //try to allocate more than total memory minus header size
    char *q = malloc(MEMSIZE-HEADSIZE+1); //should produce error message, test.c line 37
    if(q!=NULL){
        errors+=1;
    }

    return errors;
}

int overlapCheck(char *p, char *q){
    //check if two chunks overlap
    if(p + HEADSIZE + p[0]*ALIGNMENT > q){
        return 1;
    }
    return 0;
}

int addressDivBy4(char *head, char *p){
    //check if address is divisble by 4
    if((p-head) % 4 != 0){
        return 1;
    }
    return 0;
}

int chunkLocCheck(char *head, char *p){
    //check to see if chunk is outside of allocated memory
    if(p<head || p>head+MEMSIZE){
        return 1;
    }
    return 0;
}

int freeOutsideMem(char *head){
    free(head-HEADSIZE-1); //should produce error message, test.c line 69
    free(head+MEMSIZE+1); //should produce error message, test.c line 70
}

int freeNonChunk(char *p){
    int x = ((rand() % 6) * 2) + 1; //make x a random odd integer from 1 through 10
    free(p+x); // should produce error message, test.c line 76
}

int freeTwice(char *p){
    free(p);
    free(p); //should produce error message, test.c line 81
}

int main(int argc, char **argv)
{
    /*
    size_t *p = malloc(200);
    free(p);
    printA(p-2);
    */

    //size_t *z = malloc(1);
    //printB((char *)z-HEADSIZE);


    allocateZero(); //error message
    allocateLargeMemory(); //error message
   

    int numChunks = 49;
    char *chunks[numChunks+1];
    for(int i=0; i<numChunks; i++){
        int s = (rand() % 64) + 1; //generate random chunk size from 1 through 64
        chunks[i] = malloc(s);
    }

    int minAlloc = 49*(HEADSIZE+ALIGNMENT); //minimum allocated memory after random generation
    char *p = malloc(MEMSIZE-minAlloc); //chunk size too big error message, test.c line 103
    allocateZero(); //error message

    /*
    char *lastChunk = chunks[numChunks-1] - HEADSIZE; //second to last chunk
    printf("\n\nsecond last chunk size:%d\n\n",lastChunk[0]*ALIGNMENT);
    lastChunk = lastChunk + HEADSIZE + lastChunk[0]*ALIGNMENT; //get pointer to last chunk
    chunks[numChunks] = malloc(lastChunk[0]*ALIGNMENT); //allocate last chunk
    */

    printB(chunks[0]-HEADSIZE);
    //printC(chunks,numChunks+1);

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