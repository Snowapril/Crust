SHELL = /bin/sh

.SUFFIXES: .o .c .cpp
CC = g++
CFLAGS := -Wall \
          -Wextra \
          -Wpointer-arith \
          -Wcast-align \
          -Wwrite-strings \
          -Wswitch-default \
          -Wunreachable-code \
          -Winit-self \
          -Wmissing-field-initializers \
          -Wno-unknown-pragmas \
          -Wundef \
          $(DEVICE_INFO) \
          $(DEBUG_FLAGS) \
          $(MEMORY_CHECK_CFLAGS) \
          -O3
CXXFLAGS := $(CFLAGS) \
            -std=c++11
OBJS = main.o symtab.o parser.o scanner.o
TARGET = crust

$(TARGET) : $(OBJS)
	$(CC) -o $(CXXFLAGS) $(TARGET) $(OBJS)

symtab.o : ast/symtab.cpp
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
