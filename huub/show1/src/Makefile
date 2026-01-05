
CC=gcc
CFLAGS=-Wall -std=c2x

C_SOURCES := $(wildcard *.c)

C_EXECS := $(C_SOURCES:.c=) 
C_OBJS := $(C_SOURCES:.c=.o) 
C_ASMS := $(C_SOURCES:.c=.s) 

C_CLEAN_TARGETS := $(C_OBJS) $(C_EXECS) $(C_ASMS) a.out

%.s : %.c
	$(CC) -S -O0 $(CFLAGS) $(CPPFLAGS) $<

what:
	@echo "But what do you want me to make?" >&2

all: $(C_EXECS)

clean:
	rm -f $(C_CLEAN_TARGETS)

tell:
	@echo "C_SOURCES =" $(C_SOURCES)
	@echo "C_OBJS =" $(C_OBJS)
	@echo "C_EXECS =" $(C_EXECS)
	@echo "C_ASMS =" $(C_ASMS)
	@echo "C_CLEAN_TARGETS =" $(C_CLEAN_TARGETS)
