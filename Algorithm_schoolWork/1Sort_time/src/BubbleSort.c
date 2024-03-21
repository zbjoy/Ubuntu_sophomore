#include "BubbleSort.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void BubbleSort(int nums[], int n)
{
    /* struct timeval stop, start; */
    /* gettimeofday(&start, NULL); */

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (nums[i] > nums[j])
            {
                swap(&nums[i], &nums[j]);
            }
        }
    }

    /* gettimeofday(&stop, NULL); */

    /* printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); */
}
