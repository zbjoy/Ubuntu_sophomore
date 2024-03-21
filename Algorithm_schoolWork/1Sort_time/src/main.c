#include <stdio.h>
#include <stdlib.h>
#include "BubbleSort.h"

int* m_Accept_Create(int** nums, int* n);
void m_Accept_Delete(int** nums);
int main()
{
    int n = 0;
    int* nums = NULL;

    m_Accept_Create(&nums, &n);

    BubbleSort(nums, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", nums[i]);
    }

    m_Accept_Delete(&nums);
    return 0;
}

int* m_Accept_Create(int** nums, int* n)
{
    scanf("%d", &(*n));
    *nums = (int*)malloc(sizeof(int) * (*n));
    for (int i = 0; i < *n; i++)
    {
        scanf("%d", &(*nums)[i]);
    }

    return *nums;
}
void m_Accept_Delete(int** nums)
{
    if (*nums != NULL)
    {
        free(*num);
        *nums = NULL;
    }
}
