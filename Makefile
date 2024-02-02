CC = g++
CFLAGS = -Wall
LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

all: prog

prog: untitled.cpp
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	rm -f prog

