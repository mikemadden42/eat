PROGRAMS = eat

CC = c++
CFLAGS=-Wall -O2 -std=c++17
LIBS=-lboost_program_options

all: $(PROGRAMS)

.cc: ; $(CC) $(CFLAGS) $@.cc $(LIBS) -o $@
	strip $@

clean:
	rm $(PROGRAMS)
