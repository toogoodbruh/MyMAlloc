#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEM_LENGTH  4096

static char memory[MEM_LENGTH];

void *mymalloc(size_t size, char *file, int line){
    if(memory[0]==0){
        //initialize chunk spanning entire array
    }
    printf("%d", memory[0]); //test initialization
}

void myfree(void *ptr, char *file, int line){

}