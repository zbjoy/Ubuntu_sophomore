#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student
{
	char name[20];
	int age;
};

struct Student* initStudent();

void addStudent(struct Student* stu, char* name, int age);

void deleteStudent(struct Student* stu, int pos);

void printStudent(struct Student* stu);

#endif /* __STUDENT_H__ */
