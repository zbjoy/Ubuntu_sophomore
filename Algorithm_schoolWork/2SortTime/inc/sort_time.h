#pragma once

typedef void (*Sort)(int* nums, int n);

void print_sorttime(Sort sort, int* nums, int n);

void get_sorttime(Sort sort, int* nums, int n);
