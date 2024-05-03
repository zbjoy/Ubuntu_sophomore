#include "Mode.h"

int Mode(int *arr, int start, int end)
{
    if (start == end)
    {
        // 基线条件：单个元素，视为众数返回
        return arr[start];
    }
    else if (end - start == 1)
    {
        // 基线条件：两个相同元素，视为众数返回
        if (arr[start] == arr[end])
        {
            return arr[start];
        }
        else
        {
            return -1; // 表示无众数
        }
    }
    else
    {
        int mid = (start + end) / 2;
        int left_mode = Mode(arr, start, mid);
        int right_mode = Mode(arr, mid + 1, end);

        if (left_mode == -1 && right_mode == -1)
        {
            return -1; // 左右子区间均无众数，整个区间也无众数
        }
        else if (left_mode == -1)
        {
            return right_mode;
        }
        else if (right_mode == -1)
        {
            return left_mode;
        }
        else
        {
            // 计算左右子区间众数出现次数
            int left_count = 0, right_count = 0;
            for (int i = start; i <= mid; ++i)
            {
                if (arr[i] == left_mode)
                {
                    left_count++;
                }
            }
            for (int j = mid + 1; j <= end; ++j)
            {
                if (arr[j] == right_mode)
                {
                    right_count++;
                }
            }

            // 返回出现次数更多的众数
            return left_count >= right_count ? left_mode : right_mode;
        }
    }
}
