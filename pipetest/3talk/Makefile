TARGET = talker1 talker2
OBJS = talker1.o talker2.o

${TARGET}:${OBJS}
	gcc talker1.o -o talker1
	gcc talker2.o -o talker2

talker1.o:talker1.c
	gcc -c talker1.c -o talker1.o

talker2.o:talker2.c
	gcc -c talker2.c -o talker2.o

clean:
	rm -rf ${OBJS} ${TARGET}
