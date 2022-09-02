CC = g++
TEST = test
TEST_SRC = test.cpp
all:
	${CC} -o ${TEST} ${TEST_SRC}
clean:
	rm -rf ${TEST}
