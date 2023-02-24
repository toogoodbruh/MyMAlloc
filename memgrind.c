#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "mymalloc.h"

int main(int argc, char **argv)
{
    int outerLim = 50;
    int innerLim = 120;
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
    endTime = ((end.tv_sec * 1000 + end.tv_sec/1e6) - (start.tv_sec *1000 + start.tv_usec/1e6)) / 50;
    printf("\n(Test 1) Allocating and immediately freeing 1 byte chunks took %f microseconds\n", endTime);

    struct timeval start2, end2;
    char *arr [innerLim];
    gettimeofday(&start2, NULL); //get start time
    for (i = 0; i < outerLim; i++){ // performance test 2
        for (j = 0; j < innerLim; j++){ //allocate chuck of size 1 byte, store pointers in an arry
            p = malloc(sizeof(char));
            arr[j] = p;
        }
        for (j = 0; j < innerLim; j++) { //free all allocated chunks stored in the array
            free(arr[j]);
        }
    }
    gettimeofday(&end2, NULL); //get end time
    endTime = ((end2.tv_sec * 1000 + end2.tv_sec/1e6) - (start2.tv_sec *1000 + start2.tv_usec/1e6)) / 50;
    printf("\n(Test 2) Allocating %d chunks, freeing them after finishing allocation took %f microseconds\n", innerLim, endTime);
    
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
    endTime = ((end3.tv_sec * 1000 + end3.tv_sec/1e6) - (start3.tv_sec *1000 + start3.tv_usec/1e6)) / 50;
    printf("\n(Test 3) Randomly allocating and freeing chunks of data, calling malloc %d times took %f microseconds\n", innerLim, endTime);

    struct timeval start4, end4;
    int pSize = 4000;
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
    endTime = ((end4.tv_sec * 1000 + end4.tv_sec/1e6) - (start4.tv_sec *1000 + start4.tv_usec/1e6)) / 50;
    printf("\n(Test 4) Allocating and freeing chunks of data of size 4000, calling malloc %d times took %f microseconds\n", innerLim, endTime);

    //fill entire memory with 1-byte chunks until full, then free backwards, then 2-byte chunks, etc.
    //all the way until reach max size of chunks
    //then repeat 50 times :D
    struct timeval start5, end5;
    char *arr3[innerLim];
    int chunkSize = sizeof(char) ;
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
