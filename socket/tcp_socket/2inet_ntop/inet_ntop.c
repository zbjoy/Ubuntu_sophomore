#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <arpa/inet.h>

int main(void)
{
	char* ip = "127.0.0.1";
	unsigned int num = 0;
	char buf[16] = "";
	inet_pton(AF_INET, ip, &num);
	unsigned char* p = (unsigned char*)&num;
	printf("%d %d %d %d\n", p[0], p[1], p[2], p[3]);
	inet_ntop(AF_INET, &num, buf, INET_ADDRSTRLEN);
	printf("%s\n", buf);
	return 0;
}
