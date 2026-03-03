CC=gcc
CFLAGS=-Wall -Wextra -std=c11

all: programa

programa: src/p1-dataProgram.c
	$(CC) $(CFLAGS) src/p1-dataProgram.c -o programa

clean:
	rm -f programa