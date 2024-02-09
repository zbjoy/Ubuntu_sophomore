#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("usage: ./a.out ip port\n");	
		return 1;
	}
	int lfd;
	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd == -1)
	{
		perror("socket");	
		return 1;
	}

	int maxfd = lfd;

	fd_set oldset;
	fd_set rset;
	FD_ZERO(&oldset);
	FD_ZERO(&rset);

	FD_SET(lfd, &oldset);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	short port = atoi(argv[2]);
	addr.sin_port = htons(port);
	inet_pton(AF_INET, argv[1], &addr.sin_addr.s_addr);

	bind(lfd, (struct sockaddr*)&addr, sizeof(addr));

	listen(lfd, 128);
	printf("is listening......\n");

	while(1)
	{
		rset = oldset;
		int n = select(maxfd + 1, &rset, NULL, NULL, NULL);
		printf("is selecting......\n");
		if(n < 0)	
		{
			perror("select");	
			return 1;
		}
		else if(n == 0)
		{
			perror("select");	
			return 1;
		}
		else
		{
			if(FD_ISSET(lfd, &rset))	
			{
				struct sockaddr_in cliaddr;
				socklen_t clilen = sizeof(cliaddr);
				int ret = accept(lfd, (struct sockaddr*)&cliaddr, &clilen);	
				if(ret == -1)
				{
					perror("accept");	
					return 1;
				}
				printf("client connect......\n");

				FD_SET(ret, &oldset);

				if(maxfd < ret)
				{
					maxfd = ret;	
				}

				if(--n <= 0)
				{
					continue;	
				}

			}

			for(int i = lfd + 1; i <= maxfd; i++)	
			{
				if(FD_ISSET(i, &rset))
				{
					char buf[1500] = "";	
					int num = read(i, buf, sizeof(buf));
					if(num < 0)
					{
						perror("read");	
						FD_CLR(i, &oldset);
						close(i);
						continue;
					}
					else if(num == 0)
					{
						perror("read(0)");	
						FD_CLR(i, &oldset);
						close(i);
						continue;
					}
					else
					{
						write(STDOUT_FILENO, buf, num);	
						write(i, buf, num);
					}
				}	
			}
		}
	}
	
	return 0;
}
