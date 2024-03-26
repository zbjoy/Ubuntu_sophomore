#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>

int isDataHaving();

int getdata_file(int** nums, int* n, char* path);

int getdata_pipe(int** nums, int* n);

void getdata_delete(int** nums);
