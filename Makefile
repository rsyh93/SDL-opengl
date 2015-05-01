.PHONY: run clean

all: blink movement

blink:
	g++ -o blink blink.cpp -lm -lGL -lGLU `sdl-config --libs`
movement:
	g++ -o movement movement.cpp `pkg-config glu --cflags --libs` `sdl-config --libs --cflags`
clean:
	rm -f blink movement
run: blink
	./blink

run_blink: blink
	./blink
run_movement: movement
	./movement
