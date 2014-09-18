blink:
	g++ -o test blink.cpp -lm -lGL -lGLU `sdl-config --libs`
movement:
	g++ -o movement movement.cpp `pkg-config glu --cflags --libs` `sdl-config --libs --cflags`
clean:
	rm test
