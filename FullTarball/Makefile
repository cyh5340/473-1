input = 1
test = TestFiles
out = test-out
SOURCES = ./$(test)/TestInputs/test$(input).c my_memory.c
INCLUDE = ./$(test)/TestInputs/
CC = gcc
LIBS = -lm -lrt
all: 	my_memory.c ./$(test)/TestInputs/memalloc.h 
	$(CC) $(LIBS) -I$(INCLUDE) -w -o $(out) $(SOURCES)
	./$(out)
	diff test$(input)_output.txt ./$(test)/TestOutputs/test$(input)_output.txt 

run: 
	./$(out)

compile: my_memory.c ./$(test)/TestInputs/memalloc.h
	$(CC) $(LIBS) -I$(INCLUDE) -w -o $(out) $(SOURCES)
