CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

TARGET = sort_demo
SRCS = main.c selection_sort.c insertion_sort.c bubble_sort.c merge_sort.c quick_sort.c heap_sort.c sort.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c sort.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean