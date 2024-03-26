#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include "getdata.h"

int isDataHaving()
{
    fd_set rfd;
    FD_ZERO(&rfd);
    FD_SET(STDIN_FILENO, &rfd);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    int res = select(STDIN_FILENO + 1, &rfd, NULL, NULL, &timeout);
    if (res == -1)
    {
        perror("select error:");
        return -1;
    }

    if (res == 0)
    {
        return 0;
    }
    
//    if (FD_ISSET(STDIN_FILENO, &rfd))
//    {
    return 1;
//    }
}

int getdata_file(int** nums, int* n, char* path)
{
    FILE* rfd = fopen(path, "r");
    if (rfd == NULL)
    {
        perror("fopen");
        return -1;
    }
    char buf[1024] = {};
    if(!fgets(buf, sizeof(buf), rfd))
    {
        perror("fgets");
        return -1;
    }
    buf[sizeof(buf) - 1] = '\0';
    *n = atoi(buf);
    *nums = (int*)malloc(sizeof(int) * (*n));
    for (int i = 0; i < *n; i++)
    {
        memset(buf, 0, sizeof(buf));
        fgets(buf, sizeof(buf), rfd);
        buf[sizeof(buf) - 1] = '\0';
        (*nums)[i] = atoi(buf);
    }

    fclose(rfd);
    return 0;
}

int getdata_pipe(int** nums, int* n)
{
    if (!isDataHaving())
    {
        getdata_file(nums, n, "/home/zbjoy/Ubuntu_sophomore/Algorithm_schoolWork/1Sort_time/res/dataset/data_1000");
        return 0;
    }

    scanf("%d", &(*n));
    *nums = (int*)malloc(sizeof(int) * (*n));
    for (int  i = 0; i < *n; i++)
    {
        scanf("%d", &((*nums)[i]));
    }
    return 0;
}

void getdata_delete(int** nums)
{
    if (*nums != NULL)
    {
        free(*nums);
        *nums == NULL;
    }
}
