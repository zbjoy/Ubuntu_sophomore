#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <arpa/inet.h>

int main(void)
{
	unsigned int num = 0;
	int ret = inet_pton(AF_INET, "192.168.2.36", &num);
	//printf("%u\n", num);
	unsigned char* p = (unsigned char*)&num;
	printf("%d %d %d %d\n", p[0], p[1], p[2], p[3]);
	return 0;
}
