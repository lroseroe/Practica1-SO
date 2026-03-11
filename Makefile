CC=gcc
CFLAGS=-Wall -Wextra -std=c11 `pkg-config --cflags gtk4`
LIBS=`pkg-config --libs gtk4`

all: programa

programa: src/CSV.c src/GUI.c
	$(CC) $(CFLAGS) src/CSV.c src/GUI.c -o programa $(LIBS)

clean:
	rm -f programa