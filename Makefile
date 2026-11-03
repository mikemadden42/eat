PROGRAMS = eat

CXX = c++
CXXFLAGS = -Wall -Wextra -pedantic -O2 -std=c++17
LIBS =

.PHONY: all clean

all: $(PROGRAMS)

%: %.cc
	$(CXX) $(CXXFLAGS) $< $(LIBS) -o $@
	strip $@

clean:
	rm -f $(PROGRAMS)
