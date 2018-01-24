CFLAGS = -lGL -lglut -lGLU
default: build
build: main
run: main.o
	g++ main.cpp -lGL -lglut -lGLU -o main
	./main