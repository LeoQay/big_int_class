CC=g++
PROJECT_NAME=bigint
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread
TEST_NAME=test_$(PROJECT_NAME)
CPP_FILE=$(PROJECT_NAME).cpp
HPP_FILE=$(PROJECT_NAME).hpp
OBJ_FILE=$(PROJECT_NAME).o

.PHONY: test clean

all: make_test

make_test:  $(OBJ_FILE)
	$(CC) $(FLAGS) $(TEST_NAME).cpp $(OBJ_FILE) -o $(TEST_NAME) $(TEST_LIBS)

$(OBJ_FILE): $(CPP_FILE) $(HPP_FILE)
	$(CC) $(FLAGS) $(CPP_FILE) -c

test:
	./$(TEST_NAME)

clean:
	rm -f *.o $(TEST_NAME)
