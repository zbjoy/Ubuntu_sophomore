#include <stdio.h>
#include "student.h"

void func(struct Student*);

int main(void)
{
	struct Student* stu = initStudent();
	func(stu);
	return 0;
}

void func(struct Student* stu)
{
	addStudent(stu, "张三", 15);
    addStudent(stu, "王五", 18);
    printStudent(stu);
 	deleteStudent(stu, 0);
    printf("*********************************************\n");
	printStudent(stu);
}
