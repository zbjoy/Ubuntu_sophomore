TARGET = ./bin/test
SRC = $(wildcard ./src/*.c)
OBJS = $(patsubst ./src/%.c, ./obj/%.o, ${SRC})


INC = ./inc


${TARGET}:${OBJS}
	gcc $^ -o $@

./obj/%.o:./src/%.c
	gcc -c $< -I${INC} -o $@

clean:
	rm -rf ./obj/*.o

give:
	ar -rcs libtest.a ./obj/*.o
	mkdir give
	rm -rf /obj/test.o
	gcc src/test.c -I./inc -L./ -ltest -o give.out
	cp ./inc/* ./give/ -r
	cp ./src/test.c ./give
	mv give.out ./give
	mv libtest.a ./give
	make clean
