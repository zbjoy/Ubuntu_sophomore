#include <stdio.h>
#include <sys/timerfd.h>
#include <stdint.h>
#include <unistd.h>

int main()
{
    int iTimerFd = timerfd_create(CLOCK_MONOTONIC, 0);
    struct itimerspec period = {
        {5, 0}, {5, 0}
    };
    timerfd_settime(iTimerFd, 0, &period, NULL);
    uint64_t count = 0;

    while (1)
    {
        read(iTimerFd, &count, sizeof(count));
        printf("timeout 5 seconds\n");
    }
    return 0;
}
