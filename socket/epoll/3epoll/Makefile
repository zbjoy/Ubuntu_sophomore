SRC = $(wildcard ./*.c)
OBJS = $(patsubst %.c, %.o, ${SRC})

TARGET = server

${TARGET}:${OBJS}
	gcc $^ -o $@

%.o:%.c
	gcc -c $< -o $@

clean:
	-rm -rf ${OBJS} ${TARGET} 
