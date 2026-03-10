CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c11

all: build_name_index search_name build_publisher_index search_publisher

build_name_index: build_name_index.c common.c common.h
	$(CC) $(CFLAGS) -o build_name_index build_name_index.c common.c

search_name: search_name.c common.c common.h
	$(CC) $(CFLAGS) -o search_name search_name.c common.c

build_publisher_index: build_publisher_index.c common.c common.h
	$(CC) $(CFLAGS) -o build_publisher_index build_publisher_index.c common.c

search_publisher: search_publisher.c common.c common.h
	$(CC) $(CFLAGS) -o search_publisher search_publisher.c common.c

clean:
	rm -f build_name_index search_name build_publisher_index search_publisher *.o *.bin