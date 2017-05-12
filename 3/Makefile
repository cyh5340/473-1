input=1
CFLAGS = -w -g
LIBS = -lm
INCLUDE = -I./TestFiles/TestInputs/
OUT = test-out
SOURCES = ./TestFiles/TestInputs/test$(input).c 473_mm.c
all: 	473_mm.c TestFiles/TestInputs/473_mm.h 
	gcc $(CFLAGS) $(INCLUDE) $(LIBS) -o $(OUT) $(SOURCES) 
	./$(OUT)
	diff test$(input).txt ./TestFiles/TestOutputs/test$(input).txt 

run: 
	./test-out

compile: 473_mm.c TestFiles/TestInputs/473_mm.h
	gcc $(CFLAGS) $(INCLUDE) $(LIBS) -o $(OUT) $(SOURCES) 
