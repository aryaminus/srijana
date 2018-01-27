CFLAGS = -lGL -lglut -lGLU
default: build
build: main
run: main.o
	g++ main.cpp -lGL -lglut -lGLU -o main
	./main
snake: main.o
	g++ snake.cpp -lGL -lglut -lGLU -o snake
	./snake