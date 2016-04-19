OBJS = Main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

Main.o : Main.cpp
	$(CC) $(CFLAGS) Main.cpp

Processor.o : Lexer.h Lexer.cpp
	$(CC) $(CFLAGS) Lexer.cpp

FileReader.o : FileReader.h FileReader.cpp
	$(CC) $(CFLAGS) FileReader.cpp

Token.o : Token.h Token.cpp
	$(CC) $(CFLAGS) Token.cpp

TokenType.o : TokenType.cpp
	$(CC) $(CFLAGS) TokenType.cpp

clean:
	\rm *.o *~ p1
