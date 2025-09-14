CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 $(EXTRA_CFLAGS)
LDFLAGS =

TARGET = main
LIBSORT = libsort.so
LIBWRAP = libtimewrap.so

SORT_SRCS = selection_sort.c insertion_sort.c bubble_sort.c merge_sort.c quick_sort.c heap_sort.c sort.c
MAIN_SRCS = main.c

SORT_OBJS = $(SORT_SRCS:.c=.o)
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

all: $(TARGET) $(LIBSORT) $(LIBWRAP)

ifdef DEBUG
EXTRA_CFLAGS += -DDEBUG_BUBBLE_TRACE
endif

$(TARGET): $(MAIN_OBJS) $(LIBSORT)
	$(CC) $(CFLAGS) -Wl,-rpath,'$$ORIGIN' -L. -o $@ $(MAIN_OBJS) -lsort

$(LIBSORT): $(SORT_OBJS)
	$(CC) -shared -fPIC -o $@ $^

$(LIBWRAP): timewrap.o
	$(CC) -shared -fPIC -o $@ $^

%.o: %.c sort.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	rm -f $(SORT_OBJS) $(MAIN_OBJS) $(TARGET) $(LIBSORT) $(LIBWRAP) timewrap.o

.PHONY: all clean