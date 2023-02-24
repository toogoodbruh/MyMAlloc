#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "mymalloc.h"

int main(int argc, char **argv)
{
    int outerLim = 50;
    int innerLim = 120;
    int memSize = 4096;
    int headerSize = 8;
    int alignment = 4;

    //test 1
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_sec);
    int randInt;
    int i, j;
    char *p;
    double endTime, startTime;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < outerLim; i++){ //performance test 1
        for (j = 0; j < innerLim; j++){ //allocate a chunk of size 1 byte, free immediately after
            p = malloc(sizeof(char));
            free(p);
        }
    }
    gettimeofday(&end, NULL);
    endTime = ((end.tv_sec * 1000 + end.tv_sec/1e6) - (start.tv_sec *1000 + start.tv_usec/1e6)) / outerLim;
    printf("\n(Test 1) Allocating and immediately freeing 1 byte chunks took, on average, %f microseconds\n", endTime);

    //test 2
    struct timeval start2, end2;
    char *arr [innerLim];
    gettimeofday(&start2, NULL); //get start time
    for (i = 0; i < outerLim; i++){ // performance test 2
        for (j = 0; j < innerLim; j++){ //allocate chunk of size 1 byte, store pointers in an arry
            p = malloc(sizeof(char));
            arr[j] = p;
        }
        for (j = 0; j < innerLim; j++) { //free all allocated chunks stored in the array
            free(arr[j]);
        }
    }
    gettimeofday(&end2, NULL); //get end time
    endTime = ((end2.tv_sec * 1000 + end2.tv_sec/1e6) - (start2.tv_sec *1000 + start2.tv_usec/1e6)) / outerLim;
    printf("\n(Test 2) Allocating %d chunks, freeing them after finishing allocation took, on average, %f microseconds\n", innerLim, endTime);
    
    //test3
    struct timeval start3, end3;
    char *arr2[innerLim];
    gettimeofday(&start3, NULL);
    for (i = 0; i < outerLim; i++){ //performance test 3
        int mallocCalls = 0, freeCount = 0; 
        while (mallocCalls < innerLim){
            randInt = rand() % 100 + 1; //random integer 
            if (randInt <= 50) {
                p = malloc(sizeof(char));
                arr2[mallocCalls] = p;
                mallocCalls++;
            } else if (freeCount < mallocCalls){ //if randInt >50 
                free(arr2[freeCount]); //free at index freeCount
                freeCount++;    
            }
        }
        while(freeCount < innerLim) { //loop ensures the remaining pointers in the array are deallocated
            free(arr2[freeCount]);
            freeCount++;
        }
    }
    gettimeofday(&end3, NULL);
    endTime = ((end3.tv_sec * 1000 + end3.tv_sec/1e6) - (start3.tv_sec *1000 + start3.tv_usec/1e6)) / outerLim;
    printf("\n(Test 3) Randomly allocating and freeing chunks of data, calling malloc %d times took, on average, %f microseconds\n", innerLim, endTime);

    /*
    test 4
    Allocate and free chunks of data that are the maximum size that mymalloc can hold, 120 times
    Repeat 50 times
    */
    struct timeval start4, end4;
    int pSize = memSize-headerSize;
    gettimeofday(&start4, NULL);
    for (i = 0; i < outerLim; i++){ //test 4
        for (j = 0; j < innerLim; j++){
            p = malloc(pSize);
            for(int k = 0; k < pSize; k++){
                p[k] = k ^ 5;
            }
            free(p);
        }
    }
    gettimeofday(&end4, NULL);
    endTime = ((end4.tv_sec * 1000 + end4.tv_sec/1e6) - (start4.tv_sec *1000 + start4.tv_usec/1e6)) / outerLim;
    printf("\n(Test 4) Allocating and freeing chunks of data of max size, calling malloc %d times took, on average, %f microseconds\n", innerLim, endTime);

    /*
    test 5
    Fill entire memory with 120 2-byte chunks, then free backwards
    Repeat with 4-byte chunks, 8-byte chunks, and 16-byte chunks.
    Iterate 50 times
    */
    struct timeval start5, end5;
    char *arr3 [innerLim];
    gettimeofday(&start5, NULL); //get start time
    for (i = 0; i < outerLim; i++){ // performance test 5
        for (j = 0; j < innerLim; j++){ //allocate chunk of size 2 byte, store pointers in an arry
            p = malloc(2);
            arr3[j] = p;
        }
        for (j = 0; j < innerLim; j++) { //free all allocated chunks stored in the array
            free(arr3[j]);
        }
    }
    gettimeofday(&end5, NULL); //get end time
    endTime = ((end5.tv_sec * 1000 + end5.tv_sec/1e6) - (start5.tv_sec *1000 + start5.tv_usec/1e6)) / outerLim;
    printf("\n(Test 5) Allocating %d 2-byte chunks, freeing them after finishing allocation took, on average, %f microseconds\n", innerLim, endTime);
   
   /*
    struct timeval start5, end5;
    char *arr3[innerLim];
    int chunkSize = 2;
    int maxChunkSize = 16;
    gettimeofday(&start5, NULL);
    /*for (i = 0; i < outerLim; i++) {
        for (j = 0; j < innerLim; j++){ 
            p = malloc(sizeof(char)*2);
            arr3[j] = p;
            for (int k = 0; k < (sizeof(char)*2); k++) {
                p[k] = 10;
            }
        }
        for(j = 0; j < innerLim; j++){
            free(arr3[j]);
        }
    }*/
    return EXIT_SUCCESS;
}
