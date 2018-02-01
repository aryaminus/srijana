CFLAGS = -lGL -lglut -lGLU
default: build
build: main
run: main.o
	g++ main.cpp -lGL -lglut -lGLU -o main
	./main
snake: main.o
	g++ new_main.cpp -lGL -lglut -lGLU -o new_main
	./new_main