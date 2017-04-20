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
	}else{
		int a = rand() % 4;
        // same as in max_q
		if(a == 0){
			sx1 = sx + 1;
			sy1 = sy;
			if(check_body(sx1, sy1)){
				sq *last = get_last();
				sx1 = last -> x - last -> mx;
				sy1 = last -> y - last -> my;
			}	
			if(mx == -1) rev();
			else{
				mx =  1;
				my =  0;
			}
		}else if(a == 1){
			sx1 = sx - 1;
			sy1 = sy;
			if(check_body(sx1, sy1)){
				sq *last = get_last();
				sx1 = last -> x - last -> mx;
				sy1 = last -> y - last -> my;
			}
			if(mx == 1) rev();
			else{
				mx = -1;
				my =  0;
			}
		}else if(a == 2){
			sx1 = sx;
			sy1 = sy + 1;
			if(check_body(sx1, sy1)){
				sq *last = get_last();
				sx1 = last -> x - last -> mx;
				sy1 = last -> y - last -> my;
			}
			if(my == -1) rev();
			else{
				mx =  0;
				my =  1;
			}
		}else{
			sx1 = sx;
			sy1 = sy - 1;
			if(check_body(sx1, sy1)){
				sq *last = get_last();
				sx1 = last -> x - last -> mx;
				sy1 = last -> y - last -> my;
			}
			if(my == 1) rev();
			else{
				mx =  0;
				my = -1;
			}
		}
		
		float *out1 = get_q(sx1, sy1);
		new_q = out1[0];
	}
	get_q(sx1, sy1);     
}

float max_q(int sx, int sy, int food_x, int food_y){
	
	float new_q = 0.0;
	int sx1 = sx + 1; // increment in x-side
	int sy1 = sy;
	if(check_body(sx1, sy1)){
		sq *last = get_last();
		sx1 = last -> x - last -> mx; //decrement mx with x of last
		sy1 = last -> y - last -> my; //decrement my with y of last
	}

    float *out1 = get_q(sx1, sy1);

    sx1 = sx - 1; //decrement x-side
	sy1 = sy;
 	if(check_body(sx1, sy1)){
		sq *last = get_last();
		sx1 = last -> x - last -> mx;
		sy1 = last -> y - last -> my;
	}		
			
	float *out2 = get_q(sx1, sy1);

 	sx1 = sx;
	sy1 = sy + 1; //increment y-side
	if(check_body(sx1, sy1)){
		sq *last = get_last();
		sx1 = last -> x - last -> mx;
		sy1 = last -> y - last -> my;
	}		
	
	float *out3 = get_q(sx1, sy1);

	sx1 = sx;
	sy1 = sy - 1; //decrement y-side
	if(check_body(sx1, sy1)){
		sq *last = get_last();
		sx1 = last -> x - last -> mx;
		sy1 = last -> y - last -> my;
	}		
			
	float *out4 = get_q(sx1, sy1);

    if(out1[0] > out2[0]){
		if(out1[0] > out3[0]){
			if(out1[0] > out4[0]){
				new_q = out1[0];
				if(mx == -1) rev();
				else{
					mx =  1;
					my =  0;
				}
			}else{
				new_q = out4[0];
				if(my == 1) rev();
				else{
					mx =  0;
					my = -1;
				}
			}	
		}else{
			if(out3[0] > out4[0]){
				new_q = out3[0];
				if(my == -1) rev();
				else{
					mx =  0;
					my =  1;
				}
			}else{
				new_q = out4[0];
				if(my == 1) rev();
				else{
					mx =  0;
					my = -1;
				}
			}
		}
        /*
        if 1>2,
            1>3,
                1>4 set new_q to out1
                    if mx=-1 rev()
                    else mx=1,my=0
                else set new_q to out4 and others
            else if 3>4 set new_q to out3 and others
            else set new_q to out4 and others
        */
	}else{
		if(out2[0] > out3[0]){
			if(out2[0] > out4[0]){
				new_q = out2[0];
				if(mx == 1) rev();
				else{
					mx = -1;
					my =  0;
				}
			}else{
				new_q = out4[0];
				if(my == 1) rev();
				else{
					mx =  0;
					my = -1;
				}
			}	
		}else{
			if(out3[0] > out4[0]){
				new_q = out3[0];
				if(my == -1) rev();
				else{
					mx =  0;
					my =  1;
				}
			}else{
				new_q = out4[0];
				if(my == 1) rev();
				else{
					mx =  0;
					my = -1;
				}
			}
		}
	}
	return new_q;

}

bool check_body(int x, int y){
	if(x == snake -> nexploration_ratet -> x && y == snake -> nexploration_ratet -> y) return true; //nexploration_ratet x,y is same as x,y
	return false;
}

sq *get_last(){
	sq *p = snake;
	while(p -> nexploration_ratet != NULL) p = p -> nexploration_ratet; //proceed till last nexploration_ratet
	return p;
}

float *get_q(int sx, int sy){
	float inputs[6];
	inputs[0] = sqrt((sx - food_x) * (sx - food_x) + (sy - food_y) * (sy - food_y)); // Root (x)^2 + (y)^2
	inputs[1] = check(sx	, sy	); //Check no increment
	inputs[2] = check(sx + 1, sy	); //Check x increment
	inputs[3] = check(sx    , sy + 1); //Check y increment
	inputs[4] = check(sx - 1, sy); //Check x decrement
	inputs[5] = check(sx    , sy - 1); //Check y decrement
	return net -> feed(inputs); //Send Feed inputs
}

float check(int x, int y){
	sq *p = snake;
	while(p != NULL){
		if(p -> x == x && p -> y == y) //Check for each case until p's x,y is equal to x,y
			return -1.0;	
		p = p -> nexploration_ratet;
	}
	if(x > 18 || x < -18 || y > 18 || y < -18) return -1.0; //Border Case Decrement
	return 1.0;
}

void rev(){
	sq *snake2 = NULL;
	sq *p = snake;
	while(p != NULL){
		sq *tmp = (sq *)malloc(sizeof(sq));
		tmp -> x = p -> x;
		tmp -> y = p -> y;
		tmp -> mx = -1 * p -> mx; //reverse case of mx by multiplying -1
		tmp -> my = -1 * p -> my; //reverse case of mx by multiplying -1
		tmp -> nexploration_ratet = snake2; //nexploration_ratet to snake2
		snake2 = tmp;
		sq *x = p -> nexploration_ratet;
		free(p); //Memory Unallocate of P
		p = x; //put p=x
	}
	snake = snake2;
	mx = snake -> mx;
	my = snake -> my;
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