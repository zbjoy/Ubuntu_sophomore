#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>

#define SIZE 128

int getfilecount(char* filename)
{
	int count = 0;

	DIR* file = opendir(filename);
	if(file == NULL)
	{
		perror("opendir");	
		exit(1);
	}


	while(1)
	{
		char path[1024];
		memset(path, 0, 1024);
	
		struct dirent* data = readdir(file);
		if(data == NULL)
		{
			break;	
		}


		if(data->d_type == DT_DIR)
		{
			if(strcmp(data->d_name, ".") == 0 || strcmp(data->d_name, "..") == 0)
			{
				continue;	
			}
			sprintf(path, "%s/%s", filename, data->d_name);
			count += getfilecount(path);	
		}
		else if(data->d_type == DT_REG)
		{
			printf("%s/%s\n", filename, data->d_name);
			count++;	
		}
	}
	closedir(file);
	
	return count;
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("usage: ./a.out filePath\n");	
		return 1;
	}

	int total = getfilecount(argv[1]);

	printf("%s has regfile number: %d\n", argv[1], total);

	return 0;
}
