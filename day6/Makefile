CFLAGS = -g -Wall

all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp
	g++ $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f *.out