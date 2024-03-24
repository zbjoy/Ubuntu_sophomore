#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    int shmid = shmget(100, 0, 0);
    void* ptr = shmat(shmid, NULL, 0);
    printf("%s", (char*)ptr);
    shmdt(ptr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

