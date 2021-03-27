CC = gcc
CPPC = g++
LD = ld

all: junction.o
	echo "Makefile is a work in progress"

junction.o: src/junction.h src/junction.cpp
	${CPPC} src/junction.cpp -c -o junction.o
