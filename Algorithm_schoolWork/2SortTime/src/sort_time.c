#include <stdio.h>
#include <sys/time.h>
#include "sort_time.h"

void print_sorttime(Sort sort, int* nums, int n)
{
    struct timeval start, stop;
    gettimeofday(&start, NULL);

    sort(nums, n);

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
}
