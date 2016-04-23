OBJS = Main.o Lexer.o FileReader.o Token.o Tree.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1: $(OBJS)
	$(CC) $(LFLAGS) -o p1 $(OBJS)

Main.o : Main.cpp Lexer.cpp Tree.cpp
	$(CC) $(CFLAGS) Main.cpp

Lexer.o : Lexer.h FileReader.h Token.h TokenType.h Tree.h

FileReader.o : FileReader.h

Token.o : Token.h TokenType.h

Tree.o : Tree.h

clean:
	\rm *.o p1
