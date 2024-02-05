#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

void write_time(int num)
{
	printf("hello...\n");
}

int main(void)
{
	pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork error");
        exit(1);
    }

    if (pid > 0)
    {
        // 父进程退出
        exit(1);
    }
    else if (pid == 0)
    {
        // 子进程
        // 提升为会长，同时也是新进程组的组长
        setsid();

        // 更改进程的执行目录
        //chdir("/home/edu");

        // 更改掩码
        umask(0022);

        // 关闭文件描述符
    //    close(STDIN_FILENO);
    //  close(STDOUT_FILENO);
        close(STDERR_FILENO);

		struct sigaction sigact;
		sigact.sa_flags = 0;
		sigemptyset(&sigact.sa_mask);
		sigact.sa_handler = write_time;
		sigaction(SIGALRM, &sigact, NULL);

		struct itimerval act;

		act.it_interval.tv_sec = 2;
		act.it_interval.tv_usec = 0;
		// 设置第一次触发定时器时间
		act.it_value.tv_sec = 2;
		act.it_value.tv_usec = 0;
		// 开始计时
		setitimer(ITIMER_REAL, &act, NULL);

		while(1)
		{

		}
	}
	return 0;
}
