#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "BubbleSort.h"
#include "sort_time.h"
#include <sys/select.h>

int* m_Accept_Create(int** nums, int* n, int flag);
void m_Accept_Delete(int** nums);
void getdata_file(int** nums, int* n, char* arg);
int isDataHaving();
int main(int argc, char** argv)
{
    int n = 0;
    int* nums = NULL;
    int flag = 0;
    char* path = NULL;

    if(!isDataHaving())
    {
        flag = 1;
        path = "/home/zbjoy/Ubuntu_sophomore/Algorithm_schoolWork/1Sort_time/res/dataset/data_1000";
    }
    else if (argc == 2)
    {
        flag = 1;
        path = argv[1];
    }

    if (flag != 0)
    {
        getdata_file(&nums, &n, path);
    }

    m_Accept_Create(&nums, &n, flag);

    sort_time(BubbleSort, nums, n);

    m_Accept_Delete(&nums);
    return 0;
}

int* m_Accept_Create(int** nums, int* n, int flag)
{
    if (flag != 0)
    {
        return NULL;
    }

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
        free(*nums);
        *nums = NULL;
    }
}

void getdata_file(int** nums, int* n, char* arg)
{
    FILE* fp = fopen(arg, "r");
    if (fp == NULL)
    {
        printf("open error...\n");
        return;
    }

    char buf[1024] = {};
    fgets(buf, sizeof(buf), fp);
    buf[sizeof(buf) - 1] = '\0';
    *n = atoi(buf);    
    *nums = (int*)malloc(sizeof(int) * (*n));

    for (int i = 0; i < *n; i++)
    {
        fgets(buf, sizeof(buf), fp);
        buf[sizeof(buf) - 1] = '\0';
        (*nums)[i] = atoi(buf);
    }

    fclose(fp);
}


int isDataHaving()
{
    fd_set rdset;
    FD_ZERO(&rdset);
    FD_SET(STDIN_FILENO, &rdset);
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    int res = select(STDIN_FILENO + 1, &rdset, NULL, NULL, &tv);
    if (res == -1)
    {
        perror("select");
        exit(1);
    }
    else if (res > 0)
    {
        //if (FD_ISSET(STDIO_FILENO, &rdset))
        //{
        return 1;
        //}
    }
    else
    {
        return 0;
    }
}
