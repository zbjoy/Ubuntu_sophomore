#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    int shmfd = 0;
    if (-1 == (shmfd = shmget(100, 4096, IPC_CREAT | 0664)))
    {
        perror("shmget");
        return 1;
    }

    void* ptr = shmat(shmfd, NULL, 0);
    memcpy(ptr, "hello world\n", sizeof("hello world\n") + 1);
    getchar();
    shmdt(ptr);
    shmctl(shmfd, IPC_RMID, NULL);
    return 0;
}

