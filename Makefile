CC = g++
FLAGS = -Wall -Wextra -Werror
SRC = ./

main: BSTTest.cpp BST.o Node.o
	$(CC) -o $@ $^ $(FLAGS)

Node.o: Node.cpp Node.h
	$(CC) -c $< $(FLAGS)

clean:
	rm -f *.o
