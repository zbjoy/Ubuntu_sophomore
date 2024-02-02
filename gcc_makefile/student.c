#include "student.h"

struct Student* initStudent()
{
	struct Student* stu = (struct Student*)malloc(sizeof(struct Student) * 5);
	memset(stu, 0, sizeof(struct Student) * 5);
	return stu;
}

void addStudent(struct Student* stu, char* name, int age)
{
	static int nums = 0;
	if(nums >= 5)
	{
		printf("cant add\n");
		return;
	}

	strcpy(stu[nums].name, name);
	stu[nums++].age = age;
}

void printStudent(struct Student* stu)
{
	int i = 0;
	while(stu[i].name != NULL && i < 5)
	{
		printf("Name: %s, Age: %d\n", stu[i].name, stu[i].age);
		i++;
	}
}

void deleteStudent(struct Student* stu, int pos)
{
	if(pos < 0 || pos >= 5)
	{
		printf("delete error\n");
		return;
	}

	if(stu[pos].name != NULL)
	{
		//stu[pos].name = NULL;
		memset(stu[pos].name, 0, strlen(stu[pos].name) + 1);
		stu[pos].age = 0;
	}
}
