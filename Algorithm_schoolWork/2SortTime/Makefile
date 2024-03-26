TARTGET = ./bin/sort_test
SRC = $(wildcard ./src/*.c)
OBJS = $(patsubst ./src/%.c, ./obj/%.o, ${SRC})

INC = ./inc

${TARTGET}:${OBJS}
	gcc $^ -o $@

./obj/%.o:./src/%.c
	gcc -c $< -I${INC} -o $@

clean:
	rm -rf ${OBJS} ${TARTGET}

g:
	@./bin/sort_test

