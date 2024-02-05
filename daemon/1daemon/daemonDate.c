#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

void write_time(int num)
{
	time_t rawtime;
	struct tm * timeinfo;
	// 获取时间
	time(&rawtime);
#if 0
	// 转为本地时间
	timeinfo = localtime(&rawtime);
	// 转为标准ASCII时间格式
	char *cur = asctime(timeinfo);
#else
	char* cur = ctime(&rawtime);
#endif

		// 将得到的时间写入文件中
		int fd = open("/home/Ubuntu_sophomore/testlog.txt", O_RDWR | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
	{
		perror("open error");
		exit(1);
	}
	// 写文件
	int ret = write(fd, cur, strlen(cur) + 1);
	if (ret == -1)
	{
		perror("write error");
		exit(1);
	}
	// 关闭文件
	close(fd);	
}

int main(void)
{
	pid_t pid = -1;
	pid = fork();
	if(pid == -1)
	{
		perror("fork");	
		return 1;
	}

	if(pid > 0)
	{
		exit(0);	
	}

	int fd = -1;
	fd = open("test.txt", O_RDWR | O_CREAT, 0664);	
	if(fd == -1)
	{
		perror("open");	
		exit(1);
	}

	setsid();

	chdir("/");

	umask(0000);

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	struct sigaction sigact;
	sigact.sa_flags = 0;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_handler = write_time;
	sigaction(SIGALRM, &sigact, NULL);

	struct itimerval act;
	act.it_interval.tv_sec = 2;
	act.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL, &act, NULL);
	while(1)
	{
	}

	return 0;
}
