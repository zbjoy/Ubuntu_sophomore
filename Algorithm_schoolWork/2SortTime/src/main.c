#include <stdio.h>
#include <stdlib.h>
//#include "sort_time.h"
#include "getdata.h"

int main(int argc, char** argv)
{
    int* nums = NULL;
    int n = 0;
    getdata_pipe(&nums, &n);


    getdata_delete(&nums);

    return 0;
}

