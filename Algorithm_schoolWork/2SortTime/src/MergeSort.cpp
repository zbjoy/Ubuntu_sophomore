#include <stdio.h>
#include <stdlib.h>
#include "MergeSort.h"

static void merge(int* nums, int left, int mid, int right)
{
    int nLeft = mid - left + 1;
    int nRight = right - mid;
    int* leftNums = (int*)malloc(sizeof(int) * nLeft);
    int* rightNums = (int*)malloc(sizeof(int) * nRight);

    for (int i = 0; i < nLeft; i++)
    {
        leftNums[i] = nums[left + i];
    }

    for (int i = 0; i < nRight; i++)
    {
        rightNums[i] = nums[mid + 1 + i];
    }

    int cur = left;
    int l = 0;
    int r = 0;
    while (l < nLeft && r < nRight)
    {
        if (leftNums[l] > rightNums[r])
        {
            nums[cur++] = leftNums[l];
            l++;
        }
        else
        {
            nums[cur++] = rightNums[r];
            r++;
        }
    }

    while (l < nLeft)
    {
        nums[cur++] = leftNums[l++];
    }

    while (r < nRight)
    {
        nums[cur++] = rightNums[r++];
    }

    free(leftNums);
    free(rightNums);
}

static void divide(int* nums, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        divide(nums, left, mid);
        divide(nums, mid + 1, right);
        merge(nums, left, mid, right);
    }
}

void MergeSort(int* nums, int n)
{
   divide(nums, 0, n - 1); 
}

