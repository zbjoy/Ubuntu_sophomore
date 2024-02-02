SRC = $(wildcard ./*.c)
OBJS = $(patsubst %.c, %.o, ${SRC})

TARGET = test

${TARGET}:libtest.a
	gcc test.c -I./ -L./ -ltest -o $@

libtest.a:student.o
	ar -rcs $@ $^

#%.o:%.c
student.o:student.c
	gcc -c $< -o $@

clean:
	-rm -rf ${OBJS} ${TARGET} libtest.a


