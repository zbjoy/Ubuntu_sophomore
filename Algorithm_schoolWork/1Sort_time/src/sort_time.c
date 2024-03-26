#include "sort_time.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void sort_time(void (*sort)(int*, int), int* nums, int n)
{
    struct timeval stop, start;
    gettimeofday(&start, NULL);

    sort(nums, n);

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
}


