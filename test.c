#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMSIZE     4096
#define HEADSIZE    8
#define ALIGNMENT   4

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
    int numErrors = 0; //store number of times mymalloc fails correctness tests

    printf("ALLOCATION ERROR TESTING\n\n");

    numErrors+=allocateZero(); //error message
    numErrors+=allocateLargeMemory(); //error messages

    int numChunks = 50; //number of randomly generated chunks
    char *chunks[numChunks+1]; //store pointers here
    int totalSize = 0; //store total memory allocated here
    for(int i=0; i<numChunks; i++){
        int s = (rand() % 64) + 1; //generate random chunk size from 1 through 64

        int remainder = s % 4;
        if(remainder!=0){
            totalSize+=s+4-remainder+HEADSIZE;
        }
        else{
            totalSize+=s+HEADSIZE;
        }

        chunks[i] = malloc(s);
    }

    int minAlloc = 50*(HEADSIZE+ALIGNMENT); //minimum allocated memory after random generation
    char *p = malloc(MEMSIZE-minAlloc); //chunk size too big error message, test.c line 107
    if(p!=NULL){
        numErrors+=1;
    }
    numErrors+=allocateZero(); //error message

    int lastChunkSize = MEMSIZE-HEADSIZE-totalSize; //get last chunk size
    chunks[numChunks] = malloc(lastChunkSize); //allocate last chunk

    numErrors+=allocateLargeMemory(); //error messages
    numErrors+=allocateZero(); //error message
    p = malloc(1); //no memory left error message, test.c line 115. Shows that memory is full
    if(p!=NULL){
        numErrors+=1;
    }

    //prove no chunks overlap
    for(int i = 0; i<numChunks-1; i++){
        numErrors+=overlapCheck(chunks[i],chunks[i+1]);
    }

    //prove memory addresses are multiples of 4 and that no chunks are located outside of memory
    for(int i = 0; i<numChunks; i++){
        numErrors+=addressDivBy4(chunks[0],chunks[i]);
        numErrors+=chunkLocCheck(chunks[0],chunks[i]);
    }

    printf("\n\nFREE ERROR TESTING\n\n");
    freeOutsideMem(chunks[0]); //try freeing outside of allocated memory
    //show numChunks examples of trying to free a non-chunk
    for(int i = 0; i<numChunks; i++){
        freeNonChunk(chunks[0]); //numChunks error messages
    }
    
    printf("\n\nNATURAL ERRORS FROM RANDOM FREEING TEST\n\n");
    free(chunks[0]); //free first chunk
    free(chunks[numChunks]); //free last chunk

    //randomly free rest of array until one unallocated chunk is left
    p = malloc(MEMSIZE-HEADSIZE); //error message
    //free chunks until all chunks are free
    while(!p){
        int r = (rand() % (numChunks-1)) + 1; //generate random chunk size from 1 through numChunks-1
        free(chunks[r]); //free random chunk, possible error message until successful
        p = malloc(MEMSIZE-HEADSIZE); //error message until successful
    }

    printf("\n\nFREE MYMALLOC TWICE ERROR TEST\n\n");
    freeTwice(p);

    printf("\nNumber of Correctness Errors: %d", numErrors); //print number of correctness errors

    return EXIT_SUCCESS;
}