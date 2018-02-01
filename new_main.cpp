/*
 * final_main.cpp: OpenGL/GLUT C/C++ Setup graphics project
 * To compile with -lfreeglut -lglu32 -lopengl32
 */

//http://www3.ntu.edu.sg/home/ehchua/programming/opengl/cg_introduction.html -> main reference

#include <iostream>

#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

int mx;
int my;

typedef struct sq{
	int x;
	int y;
	int mx;
	int my;
	struct sq *nexploration_ratet;
} sq;

sq *snake = NULL;

void add(int x, int y){
	sq *tmp = (sq *)malloc(sizeof(sq)); // Start sq snake tmp with Memory Allocation
	tmp -> x = x;
	tmp -> y = y;
	tmp -> mx = 1;
	tmp -> my = 0;
	tmp -> nexploration_ratet = snake;
	snake = tmp;
}

void start(){
	snake = NULL;
    add(0, 0);
	add(1, 0);
	add(2, 0);
	add(3, 0);
	add(4, 0);
	mx = 1;
	my = 0;
}

int main(int argc, char** argv){
    start();
}