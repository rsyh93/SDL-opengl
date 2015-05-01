PROG = blink movement
.PHONY: run clean

all: $(PROG)

$(PROG):
	g++ -o $@ $@.cpp -lm `pkg-config glu --cflags --libs` `sdl-config --libs`
clean:
	rm -f $(PROG)
run: blink
	./blink

run_blink: blink
	./blink
run_movement: movement
	./movement
