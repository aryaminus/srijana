/*
 * final_main.cpp: OpenGL/GLUT C/C++ Setup graphics project
 * To compile with -lfreeglut -lglu32 -lopengl32
 */

//http://www3.ntu.edu.sg/home/ehchua/programming/opengl/cg_introduction.html -> main reference

#include <iostream>
#include "math.h"

#include <GL/gl.h>
#include <GL/glut.h>

#include "neural.cpp"

using namespace std;

int mx;
int my;

int food_x       =     -6;
int food_y       =     -6;

int SCREENH=450,SCREENW=450;

bool neural_check = false;

int iterations   =      0;
int	exploration_rate = 40;

int   fail_count =      0;
int sc           =      0;
float old_q      =    0.0;

typedef struct sq{
	int x;
	int y;
	int mx;
	int my;
	struct sq *nexploration_ratet;
} sq;

sq *snake = NULL;

neural *net;

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

bool check_body(int x, int y){
	if(x == snake -> nexploration_ratet -> x && y == snake -> nexploration_ratet -> y) return true; //nexploration_ratet x,y is same as x,y
	return false;
}

sq *get_last(){
	sq *p = snake;
	while(p -> nexploration_ratet != NULL) p = p -> nexploration_ratet; //proceed till last nexploration_ratet
	return p;
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

void move(){
	sq *p = snake;
	int x = p -> x;
	int y = p -> y;
	int tmx = p -> mx;
	int tmy = p -> my;
	while(p -> nexploration_ratet != NULL){
		sq *q = p -> nexploration_ratet;
		int tmp = q -> x;
		q -> x = x;
		x = tmp;

		tmp = q -> y;
		q -> y = y;
		y = tmp;

		tmp = q -> mx;
		q -> mx = tmx;
		tmx = tmp;

		tmp = q -> my;
		q -> my = tmy;
		tmy = tmp;

		p = p -> nexploration_ratet;
	}
	snake -> mx = mx;
	snake -> my = my;
	snake -> x += mx;
	snake -> y += my;
    // Setup increment case from x to mx within nexploration_ratet
}

bool tail(){
	sq *p = snake;
    //tail is touched by head
	while(p -> nexploration_ratet != NULL){
		if(p -> nexploration_ratet -> x == snake -> x && p -> nexploration_ratet -> y == snake -> y)
			return true;
		p = p -> nexploration_ratet;
	}
	return false;
}

float reward(int sx, int sy, int sx1, int sy1){
	if(snake -> x == food_x && snake -> y == food_y){
		add(food_x, food_y);//Show food
		fail_count = 0;
		sc++; //Increment sc by 1
		exploration_rate = exploration_rate / 3; //Rate decrement by 1/3 from 40%
		set_f();
		return 1000.0;
	}else if(tail()){
		fail_count = 0;
		sc = 0;
		start(); //restart
		fail_count++;
		return -100000.0;
	}else if(snake -> x > 18 || snake -> x < -18 || snake -> y > 18 || snake -> y < -18){
		//border hit
        start();
		fail_count++;
		return -1000.0;
	}
	if(fail_count > 50){
        //decrease exploration_rate for hish fail_count
		exploration_rate = 20;
	}
	float re2 = sqrt((sx1 - food_x) * (sx1 - food_x) + (sy1 - food_y) * (sy1 - food_y)); //Root. (x)^2 + (y)^2
	return -re2;
}

void itera(){
	iterations++; //Increment iterations
	int sx = snake -> x;
	int sy = snake -> y;

	float inputs[6];

	int sx1 = sx;
	int sy1 = sy;

	float new_q;

	if(rand() % 100 > exploration_rate){ //If exp_rate is less than random value
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
    move();

    sx1 = snake -> x;
	sy1 = snake -> y;

    float dout[1];
	float re = reward(sx, sy, sx1, sy1);

	dout[0] =  re + 0.9 * new_q - old_q;
	net -> learn(dout);
	old_q = new_q;
}

void timer(int = 0){
	if (neural_check){ //only when neural_check is true
		itera();
		cout << "iterations : " << iterations << " score : " << sc << endl;
	}
	glutPostRedisplay(); //marks the current window as needing to be redisplayed
	glutTimerFunc(50, timer, 0); //registers a timer callback to be triggered in a specified number of milliseconds
}

int main(int argc, char** argv){
    start();
    set_f();

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (SCREENW,SCREENH);
    glutInitWindowPosition(500, 0);
    glutCreateWindow("Srijana: User and Neural Network game");

    glutTimerFunc (400,timer,0);
}