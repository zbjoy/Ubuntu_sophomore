#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "sort_time.h"

unsigned long print_sorttime(Sort sort, int* nums, int n)
{
    struct timeval start, stop;
    int* temp = (int*)malloc(sizeof(int) * n);
    memcpy(temp, nums, sizeof(int) * n);
    gettimeofday(&start, NULL);

    sort(temp, n);

    gettimeofday(&stop, NULL);
    //printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
    free(temp);
    temp = NULL;
    return (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
}

unsigned long sort_getTime(Sort sort, int* nums, int n)
{
    struct timeval start, stop;
    gettimeofday(&start, NULL);

    sort(nums, n);

    gettimeofday(&stop, NULL);
    //printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
    return (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
}

unsigned long func_gettime(Func func, void* args, void** ret_val)
{
    struct timeval start, stop;
    gettimeofday(&start, NULL);
    if (ret_val == NULL)
    {
        func(args);
    }
    else
    {
        *ret_value = func(args);
    }
}
