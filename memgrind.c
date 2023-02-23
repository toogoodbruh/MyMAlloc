#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "mymalloc.h"


int main(int argc, char **argv)
{
    int outerLim = 1;
    int innerLim = 120;
    struct timeval tv;
    //srand(utimes(NULL));
    int randInt;
    int i, j, k = 0;
    char *p;
    double endTime, startTime;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < outerLim; i++){ //run test 50 times
        for (j = 0; j < innerLim; j++){ //allocate a chunk of size 1 byte, free immediately after
            p = malloc(sizeof(char));
            //printf("\n%d\n", *p);
            free(p);
        }
    }
    gettimeofday(&end, NULL);
    endTime = ((end.tv_sec * 1000 + end.tv_sec/1e6) - (start.tv_sec *1000 + start.tv_usec/1e6)) / 50;
    printf("\nAllocating and immediately freeing 1 byte chunks took %f microseconds\n", endTime);

///////////////////////////////////////////////////////////////////

    struct timeval start2, end2;
    char *arr [innerLim];
    gettimeofday(&start2, NULL); //get start time
    for (i = 0; i < outerLim; i++){ // run test 50 times
        for (j = 0; j < innerLim; j++){ //allocate chuck of size 1 byte, store pointers in an arry
            p = malloc(sizeof(char));
            arr[j] = p;
            //free(*p);
        }
        for (j = 0; j < innerLim; j++) { //free all allocated chunks stored in the array
            //*p = arr[j];
            free(arr[j]);
        }
    }
    gettimeofday(&end2, NULL); //get end time
    endTime = ((end2.tv_sec * 1000 + end2.tv_sec/1e6) - (start2.tv_sec *1000 + start2.tv_usec/1e6)) / 50;
    printf("\nAllocating %d chunks, freeing them after finishing allocation took %f microseconds\n", innerLim, endTime);
    
    struct timeval start3, end3;
    int randIndex;
    char *arr2[innerLim];
    gettimeofday(&start3, NULL);
    for (i = 0; i < outerLim; i++){ 
        int mallocCalls = 0, freeCount = 0;
        while (mallocCalls < innerLim){
            randInt = rand() % 10 + 1;
            if (randInt <= 5) {
                p = malloc(sizeof(char));
                arr2[mallocCalls] = p;
                //printf("\nmallocCalls: %d line: %d\n", mallocCalls, __LINE__);
                mallocCalls++;
            } else if (freeCount >= mallocCalls){
                /*p = malloc(sizeof(char));
                arr2[mallocCalls] = p;
                printf("\nmallocCalls: %d line: %d\n", mallocCalls, __LINE__);
                mallocCalls++;
                */
               int x = 0;
               
            } else {
                free(arr2[freeCount]);
                //printf("\nfreeCount: %d line: %d\n", freeCount, __LINE__);
                freeCount++;
            }
        }
        //arr2[innerLim-1] = "a";
        printf("\nfreeCount after while: %d line: %d\n", freeCount, __LINE__);
        while(freeCount < innerLim) {
            printf("\n%d\n", freeCount);
            free(arr[freeCount]);
            freeCount++;
        }
    }
    gettimeofday(&end3, NULL);
    endTime = ((end3.tv_sec * 1000 + end3.tv_sec/1e6) - (start3.tv_sec *1000 + start3.tv_usec/1e6)) / 50;
    printf("\nRandomly allocating and freeing chunks of data, calling malloc %d times took %f microseconds\n", innerLim, endTime);

    return EXIT_SUCCESS;
}
