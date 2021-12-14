SHELL = /bin/sh

.SUFFIXES: .o .c .cpp
CC = g++
CFLAGS = -c
OBJS = main.o symtab.o parser.o scanner.o node.o stmt.o type.o
TARGET = crust

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

symtab.o : ast/symtab.cpp
	$(CC) $(CFLAGS) -o $@ $< 

type.o : ast/type.cpp
	$(CC) $(CFLAGS) -o $@ $< 

node.o : ast/node.cpp
	$(CC) $(CFLAGS) -o $@ $< 

stmt.o : ast/stmt.cpp
	$(CC) $(CFLAGS) -o $@ $< 

y.tab.c : parser.y
	bison -dy $< -o $@

y.tab.h : parser.y
	bison -dy $< -o $@

scanner.c : scanner.l
	flex -o $@ $<

scanner.o : scanner.c
	$(CC) $(CFLAGS) -o $@ $< 

parser.o : y.tab.c y.tab.h
	$(CC) $(CFLAGS) -o $@ $< 

main.o : main.cpp parser.o scanner.o symtab.o
	$(CC) $(CFLAGS) -o $@ main.cpp

clean :
	rm y.tab.c y.tab.h scanner.c $(TARGET) *.o 
