#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <GL/gl.h>
#include <GL/glut.h>

#include "neural.cpp"

using namespace std;

neural *net;

int num_layers   =      2;
int num_inputs   =      6;
int num_outputs  =      1;

float learning_rate     = 0.0000001;

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

    //net -> init();

}