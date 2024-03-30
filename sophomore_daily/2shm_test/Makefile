all:write read

write:write.o
	gcc write.o -o write

read:read.o
	gcc read.o -o read

write.o:write.c
	gcc -c write.c -o write.o

read.o:read.c
	gcc -c read.c -o read.o
