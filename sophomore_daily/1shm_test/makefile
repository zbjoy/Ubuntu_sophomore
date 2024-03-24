TARGET=write,read

all:write read

write:write.o
	gcc write.o -o write

read:read.o
	gcc read.o -o read

write.o:write.c
	gcc -c write.c -o write.o
	gcc -c read.c -o read.o
