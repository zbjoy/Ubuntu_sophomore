#pragma once

typedef void (*Sort)(int* nums, int n);

typedef void* (*Func)(void*);

unsigned long print_sorttime(Sort sort, int* nums, int n);

unsigned long sort_gettime(Sort sort, int* nums, int n);

unsigned long func_gettime(Func func, void* args, void** ret_val);
