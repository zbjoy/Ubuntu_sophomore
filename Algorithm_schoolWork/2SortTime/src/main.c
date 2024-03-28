#include <stdio.h>
#include <stdlib.h>
#include "sort_time.h"
#include "getdata.h"
#include "BubbleSort.h"
#include "MergeSort.h"

int count_element(int* nums, int start, int end, int target)
{
    int count = 0;
    for (int i = start; i <= end; i++)
    {
        if (nums[i] == target)
        {
            count++;
        }
    }
    return count;
}

int mode_recursive(int* nums, int start, int end)
{
    if (start == end)
    {
        return nums[start];
    }

    if (end - start == 1)
    {
        return (count_element(nums, start, end, nums[start]) >= count_element(nums, start, end, nums[end])) ? nums[start] : nums[end];
    }

    int mid = (start + end) / 2;
    int left_mode = mode_recursive(nums, start, mid);
    int right_mode = mode_recursive(nums, mid + 1, end);

    // 比较左右众数在整体数组中的出现次数
    int left_count = count_element(nums, start, end, left_mode);
    int right_count = count_element(nums, start, end, right_mode);

    // 返回出现次数最多的众数
    return (left_count >= right_count) ? left_mode : right_mode;
}

int main(int argc, char** argv)
{
    int* nums = NULL;
    int n = 0;

    if (argc == 2)
    {
        getdata_file(&nums, &n, argv[1]);
    }
    else
    {
        getdata_pipe(&nums, &n);
    }

    printf("BubbleSort: ");
    print_sorttime(BubbleSort, nums, n);
    printf("MergeSort: ");
    /* print_sorttime(MergeSort, nums, n); */
    get_sorttime(MergeSort, nums, n);

    printf("the mode is %d\n", mode_recursive(nums, 0, n - 1));

    getdata_delete(&nums);

    return 0;
}

