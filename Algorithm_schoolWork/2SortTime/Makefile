TARTGET = ./bin/sort_test
SRC = $(wildcard ./src/*.cpp)
OBJS = $(patsubst ./src/%.cpp, ./obj/%.o, ${SRC})

INC = ./inc

${TARTGET}:${OBJS}
	g++ $^ -o $@

./obj/%.o:./src/%.cpp
	g++ -c $< -I${INC} -o $@

clean:
	rm -rf ${OBJS} ${TARTGET}

g:
	@./bin/sort_test

