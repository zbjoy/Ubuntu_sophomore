#include <stdio.h>
#include <stdlib.h>
#include "sort_time.h"
#include "getdata.h"
#include "BubbleSort.h"
#include "MergeSort.h"


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
    print_sorttime(MergeSort, nums, n);

    getdata_delete(&nums);

    return 0;
}

