#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <sys/types.h>
#include <dirent.h>

int getfilenum(char* filepath)
{
	int count = 0;

	if(filepath[0] == '/')
	{
#ifdef DEBUG
		printf("the filepath maybe a /......\n");	
#endif

	}

	DIR* file = opendir(filepath);
	if(file == NULL)
	{
		perror("opendir ");	
		return count;	
	}

	while(1)
	{
		struct dirent* filestat = readdir(file);	
		if(filestat == NULL)
		{
			perror("readdir");	
			break;
		}

		if(filestat->d_type == DT_REG)
		{
			count++;	
#ifdef DEBUG

			printf("the file is %s\n", filestat->d_name);

#endif
		}
		else if(filestat->d_type == DT_DIR)
		{

			if(strcmp(filestat->d_name, ".") == 0 || strcmp(filestat->d_name, "..") == 0)
			{
				continue;	
			}
			char filedir[1024] = "";
			sprintf(filedir, "%s/%s", filepath, filestat->d_name);
			count += getfilenum(filedir);	
		}
	}

	return count;
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("usage: ./a.out filepath\n");	
		return 1;
	}

	int count = getfilenum(argv[1]);
	printf("the reguale file num is %d\n", count);
	return 0;
}
