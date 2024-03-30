#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    int shmfd = shmget(100, 0, 0);
    void* ptr = shmat(shmfd, NULL, 0);
    printf("%s", (char*)ptr);
    shmdt(ptr);
    shmctl(shmfd, IPC_RMID, NULL);
    return 0;
}

