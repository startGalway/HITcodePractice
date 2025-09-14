# Makefile for Grade Manage System (C++)

CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic
LDFLAGS :=

TARGET := gms
SRCS := main.cpp fileop.cpp sort.cpp search.cpp calculate.cpp analysis.cpp print.cpp
HDRS := types.h fileop.h sort.h search.h calculate.h analysis.h print.h

OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean rebuild run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

run: $(TARGET)
	./$(TARGET)
