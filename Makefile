CC=gcc
CFLAGS=-Wall -Wextra -std=c11

all: programa

programa: src/main.c src/UI.c src/CSV.c
	$(CC) $(CFLAGS) src/main.c src/UI.c src/CSV.c -o programa

clean:
	rm -f programa