CC = g++
CFLAGS = -Wall -g

main: ARITH_main.o AST.o parser.o interpreter.o
    $(CC) $(CFLAGS) -o main ARITH_main.o AST.o parser.o interpreter.o

ARITH_main.o: ARITH_main.cpp AST.h parser.h interpreter.h
    $(CC) $(CFLAGS) -c ARITH_main.cpp

AST.o: AST.h

parser.o: parser.h AST.h

interpreter.o: interpreter.h parser.h AST.h