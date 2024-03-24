#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    int shmid = shmget(100, 4096, IPC_CREAT | 0664);
    void* ptr = shmat(shmid, NULL, 0);
    memcpy(ptr, "hello world", sizeof("hello world") + 1);
    getchar();
    shmdt(ptr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

