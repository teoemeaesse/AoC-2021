CFLAGS = -g -Wall

%: %.cpp
	g++ $(CFLAGS) $^ -o $@
