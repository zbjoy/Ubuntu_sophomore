TARGET = people1 people2
OBJS = people1.o people2.o

${TARGET}:${OBJS}
	gcc people1.o -o people1
	gcc people2.o -o people2

people1.o:people1.c
	gcc -c people1.c -o people1.o

people2.o:people2.c
	gcc -c people2.c -o people2.o

clean:
	rm -rf people1.o people2.o ${TARGET}
