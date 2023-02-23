#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "mymalloc.h"

int main(int argc, char **argv)
{
    struct timeval tv;
    //time_t = curtime;
    int i, j, k = 0;
    char *p;
    double endTime, startTime;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < 50; i++){ //run test 50 times
        for (j = 0; j < 120; j++){ //allocate a chunk of size 1 byte, free immediately after
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
    int *arr [120];
    gettimeofday(&start2, NULL); //get start time
    for (i = 0; i < 1; i++){ // run test 50 times
        for (j = 0; j < 10; j++){ //allocate chuck of size 1 byte, store pointers in an arry
            arr[j] = malloc(sizeof(char));
            //free(*p);
        }
        for (j = 0; j < 10; j++) { //free all allocated chunks stored in the array
            //*p = arr[j];
            free(arr[j]);
        }
    }
    gettimeofday(&end2, NULL); //get end time
    endTime = ((end2.tv_sec * 1000 + end2.tv_sec/1e6) - (start2.tv_sec *1000 + start2.tv_usec/1e6)) / 50;
    printf("\nAllocating 120 chunks, freeing them after finishing allocation took %f microseconds\n", endTime);
    

    return EXIT_SUCCESS;
}
