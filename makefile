PROG=track
OPTS=-O
OPENCV=`pkg-config opencv --cflags --libs`


all: $(PROG)

$(PROG): latency.cpp
	g++ $(OPTS) $< -o $@ $(OPENCV)

run: $(PROG)
	./$(PROG)

clean:
	- rm $(PROG)