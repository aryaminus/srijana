#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <GL/gl.h>
#include <GL/glut.h>

#include "neural.cpp"

using namespace std;

typedef struct sq{
	int x;
	int y;
	int mx;
	int my;
	struct sq *nexploration_ratet;
} sq;

sq *snake = NULL;

int mx;
int my;
neural *net;

int num_layers   =      2;
int num_inputs   =      6;
int num_outputs  =      1;

float learning_rate     = 0.0000001;

int food_x       =     -6;
int food_y       =     -6;

bool  pus        =  false;
int iterations   =      0;
int sc           =      0;
int tmp          =     50;

int	  exploration_rate  = 	     40;

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

void add(int x, int y){
	sq *tmp = (sq *)malloc(sizeof(sq)); // Start sq snake tmp with Memory Allocation
	tmp -> x = x;
	tmp -> y = y;
	tmp -> mx = 1;
	tmp -> my = 0;
	tmp -> nexploration_ratet = snake;
	snake = tmp;
}

void set_f(){
	bool f = true;
	while(f){
		srand(time(NULL));
		food_x = (rand() % 34) - 17;	 
		srand(time(NULL));
		food_y = (rand() % 34) - 17;
		sq *p = snake;
		while(p != NULL){
			if(p -> x == food_x && p -> y == food_y){
				f = true;
				break;		
			}	
			f = false;
			p = p -> nexploration_ratet;
		}	
	}
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);	
	glLoadIdentity ();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	GLfloat acolor[] = {1.4, 1.4, 1.4, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, acolor);

}

void myIdleFunc(int a) {
	if(!pus){
		itera();
	}
	cout << "iterations : " << iterations << " score : " << sc << endl;
	glutPostRedisplay();
	glutTimerFunc(tmp, myIdleFunc, 0);
}

void itera(){
	iterations++; //Increment iterations
	int sx = snake -> x; 
	int sy = snake -> y;
		
	float inputs[6];
	int sx1 = sx;
	int sy1 = sy;
	
	float new_q;
	if(rand() % 100 > exploration_rate){
		new_q = max_q(sx, sy, food_x, food_y);
	}
}



int main(int argc, char** argv){
    cout << "-----------------------------------------------" << endl;
	cout << endl;
	cout << "       --- Srijana - A OpenGL & NN Game ---    " << endl;
	cout << endl;
	cout << "written by: Sunim Acharya(72080)in cpp in linux " << endl;
	cout << endl;
	cout << "-----------------------------------------------" << endl;

    srand(time(NULL));// Set random variable as current time

    net = new neural(num_inputs, num_outputs, num_layers, 10, learning_rate); //Send neural with initial values

    net -> init();

    start(); //Start snake layout with initial values

    set_f(); //Setup food point cordinates

    glutInit(&argc,argv); //Setup glutInit
    glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Set Display window
    glutInitWindowSize(450,450); //Window Size
	glutInitWindowPosition(500,0); //Window Position
    glutCreateWindow("Srijana : A C and OpenGL game with NN"); //Window with the "..." name

    init(); //GL Setup

    glutTimerFunc(400, myIdleFunc, 0); //Timer setup



}