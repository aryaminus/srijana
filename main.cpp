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

int main(){
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

}