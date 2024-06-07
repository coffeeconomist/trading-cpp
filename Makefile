# Automated Makefile

CC = /usr/bin/g++
CFLAGS = -Wall -Werror -D_GLIBCXX_DEBUG -std=c++11 -g
COMPILE = $(CC) $(CFLAGS) -c
OBJFILES := $(patsubst %.cpp ,%.o,$(wildcard *.cpp))
PROG_NAME = merkelrex

all: myprog

myprog: $(OBJFILES)
	$(CC) -o $(PROG_NAME) $(OBJFILES)

%.o: %.cpp
	$(COMPILE) -o $@ $<

clean:
	rm -f *.o *.html $(PROG_NAME)

