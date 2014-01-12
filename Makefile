all:
	g++ -o test main.cpp -lm -lGL -lGLU `sdl-config --libs` 
clean:
	rm test
