#include <stdio.h>
#include <stdlib.h>
#include "sort_time.h"
#include "getdata.h"
#include "BubbleSort.h"
#include "MergeSort.h"
#include "Mode.h"


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

    printf("BubbleSort: took %lu\n", print_sorttime(BubbleSort, nums, n));
    //print_sorttime(BubbleSort, nums, n);
    printf("MergeSort: took %lu\n", sort_getTime(MergeSort, nums, n));
    /* print_sorttime(MergeSort, nums, n); */
    //sort_getTime(MergeSort, nums, n);

   // printf("the mode is %d\n", mode_recursive(nums, 0, n - 1));
   
    printf("Mode number is %d\n", Mode(nums, 0, sizeof(nums) / sizeof(nums[0])));

    getdata_delete(&nums);

    return 0;
}

