/*
 * final_main.cpp: OpenGL/GLUT C/C++ Setup graphics project
 * To compile with -lfreeglut -lglu32 -lopengl32
 */

//http://www3.ntu.edu.sg/home/ehchua/programming/opengl/cg_introduction.html -> main reference

//#include <windows.h>  // for MS Windows
#include <iostream>
#include <fstream>
#include<stdlib.h>
#include<stdio.h>

#include "math.h"
#include<time.h>

#include <GL/gl.h>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

#include "neural.cpp"

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
/*
GLfloat xSpeed = 0.02f;      // Ball's speed in x and y directions
GLfloat ySpeed = 0.007f;
int refreshMills = 30;      // Refresh period in milliseconds
bool pause=false;        // Movement paused or resumed
GLfloat xSpeedSaved, ySpeedSaved;  // To support resume
*/

using namespace std;

neural *net;

int num_layers   =      2;
int num_inputs   =      6;
int num_outputs  =      1;

float learning_rate     = 0.0000001;

int SCREENH=600,SCREENW=800;

int Scale = 25;
int N = 50,M = 30;
int w = Scale * N;
int h = Scale * M;

char sScore[15];
char sHightScore[15];
int Score = 0;
int hightScore;
int num = 7;
int d = 1;
int dir;
bool down=false;

//building b;  // building struct
//int level=1,buildColor;  
//Cloud s;     // cloud struct

bool pause=false,wflag = true,instflag=false,uflag=false,nflag=false;  //flags

int key1 = 3;

struct
{
    int x;
    int y;
} s[100];

class Fruct
{
public:
    int x,y;
    void New()
    {
        x = rand() % N;
        y = rand() % (M-3);
    }
    void DrawFruct()
    {
        glColor3f (1.0, 1.0, 0.0);
        glRectf (x*Scale, y*Scale, (x+1)*Scale, (y+1)*Scale);
    }
}m[2];

class Bomb
{
public:
    int x,y;

    void New()
    {
        x = rand() % N;
        y = rand() % (M-3);
    }
    void DrawBomb()
    {
        glColor3f (1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        for(float i=0; i < 2*3.14; i += 3.14/4)
        {
            glVertex2f((x+0.5)*Scale + (0.5)*Scale*(1.1)*sin(i), (y+0.5)*Scale + (0.5)*Scale*(1.1)*cos(i));
        }
        glEnd();
    }
}u[10];

void keyPressed(unsigned char,int,int);
void mouse(int button, int state, int x, int y);
void printString(float x,float y,float z,void *font,char *string);//what does this do??
void welcome();
void display();

void drawString(float x,float y,float z,void *font,char *string)
{
	char *c;
	glRasterPos3f(x, y,z);

	for (c=string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

void draw_string(void *font, const char* string)
{
    while(*string)
        glutStrokeCharacter(font, *string++);
}

void welcome()
{
	glColor3f(0.3,0.56,0.84);   //welcome background
	glBegin(GL_POLYGON);
	glVertex3f(0.0,0.0,0.0);
	glColor3f(0.137,0.137,0.556);
	glVertex3f(100.0,0.0,0.0);
	glColor3f(0.196,0.196,0.8);
	glVertex3f(100.0,100.0,0.0);
	glVertex3f(0.0,100.0,0.0);
	glEnd();

	// button 1 .. PLAY
	glColor3f(0.196,0.196,0.8);
	glRectf(39.5,39.5,60.5,45.5);

	glColor3f(0.8,0.8,0.8);
	glRectf(40,40,60,45);
	glColor3f(0.137,0.137,0.556);
	drawString(47,42,0,GLUT_BITMAP_HELVETICA_18,"USER");

	// button 2 .. instructions
	glColor3f(0.196,0.196,0.8);
	glRectf(39.5,29.5,60.5,35.5);

	glColor3f(0.8,0.8,0.8);
	glRectf(40,30,60,35);
	glColor3f(0.137,0.137,0.556);
	drawString(41,31,0,GLUT_BITMAP_HELVETICA_18,"NETWORK_PLAY");

	// button 3 .. ABOUT
	glColor3f(0.196,0.196,0.8);
	glRectf(39.5,19.5,60.5,25.5);

	glColor3f(0.8,0.8,0.8);
	glRectf(40,20,60,25);
	glColor3f(0.137,0.137,0.556);
	drawString(46,21,0,GLUT_BITMAP_HELVETICA_18,"HOW_TO");

	// button 4 .. exit
	glColor3f(0.196,0.196,0.8);
	glRectf(39.5,9.5,60.5,15.5);

	glColor3f(0.8,0.8,0.8);
	glRectf(40,10,60,15);
	glColor3f(0.137,0.137,0.556);
	drawString(47,11,0,GLUT_BITMAP_HELVETICA_18,"EXIT");


	glPushMatrix();

	glColor3f(0.8,0.8,0.8);
	drawString(25.5,92,0,GLUT_BITMAP_TIMES_ROMAN_24,"COMPUTER GRAPHICS PROJECT ");
	drawString(35.5,80,0,GLUT_BITMAP_TIMES_ROMAN_24,"SRIJANA");
	glPopMatrix();
	glColor3f(0.137,0.137,0.556);

}

void Tick()
{
    //Движение тела змейки:
    for (int i = num; i > 0; --i)
    {
        s[i].x = s[i-1].x;
        s[i].y = s[i-1].y;
    }

    //Движение головы змейки:
    switch (dir) {
        case 0:
            s[0].y+=1;
            break;
        case 1:
            s[0].x-=1;
            break;
        case 2:
            s[0].x+=1;
            break;
        case 3:
            s[0].y-=1;
            break;
    }
    int h=0;
    // Если наехали на фрукт, змейка увеличивается:
    for (int i = 0; i < 5; i++)
        if ( (s[0].x == m[i].x) && (s[0].y == m[i].y) )
        {
            num++;
            m[i].New();
            if(h!=11){
                u[h].New();
                h++;
            }
            else{
                h=0;
                u[h].New();
            }
            Score+=2;
        }

    // Если наехали на бомбу, сокращается ее длина:
    for (int i = 0; i < 10; i++)
        if ( (s[0].x == u[i].x) && (s[0].y == u[i].y) )
        {
            if (num == 2) key1=2;
            if (num > 3)
                num = num - 2;
            else
                num = 2;
            u[i].New();
            if (Score > 0)
                Score--;
            if (Score <  0)
                Score =0;
        }

    // Если вышли за границы, конец игры:
    if (s[0].x > N || s[0].x < 0 || s[0].y > (M-3) || s[0].y < 0)
    {
        key1=2;
    }

    // Если змейка наехала сама на себя, сокращается ее длина:
    for (int i = 1; i < num; i++)
        if (s[0].x == s[i].x && s[0].y == s[i].y ){
            num = 3;
            if (Score > 0)
                Score-=3;
            if (Score < 0)
                Score = 0;
        }
}

void DrawSnake()
{
    glColor3f (0.0,1.0,0.0);
    for (int i = 0; i < num; i++)
    {
        glRectf (s[i].x*Scale, s[i].y*Scale, (s[i].x+1)*Scale, (s[i].y+1)*Scale);
    }
}

void DrawScore()
{
    glLineWidth(1.5f);
    glColor3f (1.1,1.0,1.0);

    glPushMatrix();
    glTranslatef(w/(5.4), h/(1.05), 0);
    glScalef(0.3f, 0.3f, 0.3f);
    draw_string(GLUT_STROKE_ROMAN, "Your score:");
    glPopMatrix();
    sprintf(sScore, "%9d", Score);
    glPushMatrix();
    glTranslatef(w/(5), h/(1.05), 0);
    glScalef(0.3f, 0.3f, 0.3f);
    draw_string(GLUT_STROKE_ROMAN, sScore);
    glPopMatrix();

    ifstream inFile("Snake.bin",ios_base::binary);
    while(inFile.peek()!=EOF)
        inFile >> sHightScore;
    inFile.close();
    hightScore = atoi(sHightScore);
    glPushMatrix();
    glTranslatef(w/(1.6), h/(1.05), 0);
    glScalef(0.3f, 0.3f, 0.3f);
    draw_string(GLUT_STROKE_ROMAN, "Hide score:");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(w/(1.2), h/(1.05), 0);
    glScalef(0.3f, 0.3f, 0.3f);
    draw_string(GLUT_STROKE_ROMAN, sHightScore);
    glPopMatrix();

    glFinish();
    glutSwapBuffers();
}

void DrawRules()
{
		glColor3f(0.3,0.56,0.84);   // background
		glBegin(GL_POLYGON);
		glVertex3f(0.0,0.0,0.0);
		glColor3f(0.137,0.137,0.556);
		glVertex3f(100.0,0.0,0.0);
		glColor3f(0.196,0.196,0.8);
		glVertex3f(100.0,100.0,0.0);
		glVertex3f(0.0,100.0,0.0);
		glEnd();
		glPushMatrix();
		glScalef(0.8,0.8,0);
		glPopMatrix();
		glColor3f(0.137,0.137,0.556);
		glRectf(20.0,20.0,80.0,80.0);
		glColor3f(0.8,0.8,0.8);
		glRectf(21.0,21.0,79.0,79.0);


		glColor3f(0.196,0.196,0.8);
		glRectf(40,5,60,10);
		glColor3f(0.8,0.8,0.8);
		glRectf(40.5,5.5,59.5,9.5);

		glColor3f(0.137,0.137,0.556);
		drawString(46,6,0,GLUT_BITMAP_TIMES_ROMAN_24,"BACK");

		glColor3f(0.137,0.137,0.556);
		drawString(37,75,0,GLUT_BITMAP_TIMES_ROMAN_24,"HOW TO PLAY");
		drawString(23,69,0,GLUT_BITMAP_HELVETICA_18,"- Click and hold mouse left key to gain altitude of ");
		drawString(23,65,0,GLUT_BITMAP_HELVETICA_18,"    the plane.");
		drawString(23,61,0,GLUT_BITMAP_HELVETICA_18,"- Release the mouse left key to reduce the altitude.");
		drawString(23,57,0,GLUT_BITMAP_HELVETICA_18,"- Use the Right mouse key to speed up the plane(NOS)");
		drawString(23,53,0,GLUT_BITMAP_HELVETICA_18,"- Main aim of the game is to avoid the obstacles ");
		drawString(23,49,0,GLUT_BITMAP_HELVETICA_18,"    such as buildings and clouds.");
		drawString(23,45,0,GLUT_BITMAP_HELVETICA_18,"- Also the meter at the bottom shows the distance ");
		drawString(23,41,0,GLUT_BITMAP_HELVETICA_18,"    travelled,NITROS left,Atitude and the LEVEL.");
		drawString(23,37,0,GLUT_BITMAP_HELVETICA_18,"- As you reach distance multples of 50 tour level ");
		drawString(23,33,0,GLUT_BITMAP_HELVETICA_18,"    increases as well as the speed of the plane.");
		drawString(33,27,0,GLUT_BITMAP_HELVETICA_18," ENJOY PLAYING THE GAME");

		glutPostRedisplay();
}

void DrawExit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f (0.0, 0.16, 0.0);
    glVertex3f (750.0, 150.0, 0.0);
    glColor3f (0.0, 0.19, 0.0);
    glVertex3f (500.0, 150.0, 0.0);
    glColor3f (0.0, 0.16, 0.0);
    glVertex3f (500.0, 90.0, 0.0);
    glColor3f (0.0, 0.19, 0.0);
    glVertex3f (750.0, 90.0, 0.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f (0.0, 0.16, 0.0);
    glVertex3f (670.0, 80.0, 0.0);
    glColor3f (0.0, 0.19, 0.0);
    glVertex3f (580.0, 80.0, 0.0);
    glColor3f (0.0, 0.16, 0.0);
    glVertex3f (580.0, 30.0, 0.0);
    glColor3f (0.0, 0.19, 0.0);
    glVertex3f (670.0, 30.0, 0.0);
    glEnd();

    glLineWidth(7.0f);
    glColor3f (1.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(w/(6), h/(1.5), 0);
    glScalef(1.1f, 1.1f, 1.1f);
    draw_string(GLUT_STROKE_ROMAN, "Game over!");
    glPopMatrix();

    glLineWidth(2.5f);
    glColor3f (0.0,1.0,1.0);
    glPushMatrix();
    glTranslatef(w/(2.4), h/7, 0);
    glScalef(0.2f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "Return to MENU");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(w/(2.07), h/(15.3), 0);
    glScalef(0.2f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "EXIT");
    glPopMatrix();

    glLineWidth(3.5f);
    glColor3f (0.9,0.3,0.5);
    glPushMatrix();
    glTranslatef(w/(2.8), h/(2.1), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, "Final score:");
    glPopMatrix();

    sprintf(sScore, "%9d", Score);
    glPushMatrix();
    glTranslatef(w/(2.8), h/(2.1), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, sScore);
    glPopMatrix();

    ifstream inFile("Snake.bin",ios_base::binary);
    while(inFile.peek()!=EOF) inFile >> sHightScore;
    inFile.close();
    hightScore = atoi(sHightScore);
    if ( Score > hightScore )
    {
        sprintf(sHightScore, "%9d", Score);
        ofstream outFile("Snake.bin",ios_base::binary);
        outFile << sScore;
        outFile.close();
    }
    glPushMatrix();
    glTranslatef(w/(2.8), h/(2.55), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, "Hide score:");
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(w/(1.6), h/(2.55), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, sHightScore);
    glPopMatrix();

    glFinish();
    glutSwapBuffers();
}

/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
   
  srand(time(0));
}

/* Callback handler for window re-paint event */
/*
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear the color buffer (background)
   welcome();
   glFlush();  // Render now
   glutSwapBuffers();
}
*/

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (key1)
    {
        case 1:
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_POLYGON);
            glColor3f (0.0, 0.3, 0.0);
            glVertex3f (0.0, 800.0, 0.0);
            glColor3f (0.0, 0.11, 0.0);
            glVertex3f (0, 700.0, 0.0);
            glColor3f (0.0, 0.11, 0.0);
            glVertex3f (1400.0, 700.0, 0.0);
            glColor3f (0.0, 0.3, 0.0);
            glVertex3f (1400.0, 800.0, 0.0);
            glEnd();
            for( int i = 0; i < 2; i++)
                m[i].DrawFruct();
            for( int i = 0; i < 10; i++)
                u[i].DrawBomb();
            DrawSnake();
            DrawScore();
            break;
        case 2:
            DrawExit();
            break;
        case 3:
            welcome();
            break;
        case 4:
            DrawRules();
            break;
    }
    glFlush();
	//GameOver Checking
	/*
	if(wflag==true)//Welcome Screen
	{
		welcome();
	}
	else if(uflag==true)//User Screen
	{
		glColor3f(0.3,0.56,0.84);   // background
		glBegin(GL_POLYGON);
		glVertex3f(0.0,0.0,0.0);
		glColor3f(0.137,0.137,0.556);
		glVertex3f(100.0,0.0,0.0);
		glColor3f(0.196,0.196,0.8);
		glVertex3f(100.0,100.0,0.0);
		glVertex3f(0.0,100.0,0.0);
		glEnd();
		glPushMatrix();
		glScalef(0.8,0.8,0);
		glPopMatrix();
		glColor3f(0.137,0.137,0.556);
		glRectf(20.0,20.0,80.0,80.0);
		glColor3f(0.8,0.8,0.8);
		glRectf(21.0,21.0,79.0,79.0);


		glColor3f(0.196,0.196,0.8);
		glRectf(40,5,60,10);
		glColor3f(0.8,0.8,0.8);
		glRectf(40.5,5.5,59.5,9.5);

		glColor3f(0.137,0.137,0.556);
		drawString(46,6,0,GLUT_BITMAP_TIMES_ROMAN_24,"BACK");

		glColor3f(0.137,0.137,0.556);
		drawString(37,75,0,GLUT_BITMAP_TIMES_ROMAN_24,"HOW TO PLAY");
		drawString(23,69,0,GLUT_BITMAP_HELVETICA_18,"- Click and hold mouse left key to gain altitude of ");
		drawString(23,65,0,GLUT_BITMAP_HELVETICA_18,"    the plane.");
		drawString(23,61,0,GLUT_BITMAP_HELVETICA_18,"- Release the mouse left key to reduce the altitude.");
		drawString(23,57,0,GLUT_BITMAP_HELVETICA_18,"- Use the Right mouse key to speed up the plane(NOS)");
		drawString(23,53,0,GLUT_BITMAP_HELVETICA_18,"- Main aim of the game is to avoid the obstacles ");
		drawString(23,49,0,GLUT_BITMAP_HELVETICA_18,"    such as buildings and clouds.");
		drawString(23,45,0,GLUT_BITMAP_HELVETICA_18,"- Also the meter at the bottom shows the distance ");
		drawString(23,41,0,GLUT_BITMAP_HELVETICA_18,"    travelled,NITROS left,Atitude and the LEVEL.");
		drawString(23,37,0,GLUT_BITMAP_HELVETICA_18,"- As you reach distance multples of 50 tour level ");
		drawString(23,33,0,GLUT_BITMAP_HELVETICA_18,"    increases as well as the speed of the plane.");
		drawString(33,27,0,GLUT_BITMAP_HELVETICA_18," ENJOY PLAYING THE GAME");

		glutPostRedisplay();
	}
	else if(nflag==true)//Neural Network Screen
	{
		glColor3f(0.3,0.56,0.84);   // background
		glBegin(GL_POLYGON);
		glVertex3f(0.0,0.0,0.0);
		glColor3f(0.137,0.137,0.556);
		glVertex3f(100.0,0.0,0.0);
		glColor3f(0.196,0.196,0.8);
		glVertex3f(100.0,100.0,0.0);
		glVertex3f(0.0,100.0,0.0);
		glEnd();
		glPushMatrix();
		glScalef(0.8,0.8,0);
		glPopMatrix();
		glColor3f(0.137,0.137,0.556);
		glRectf(20.0,20.0,80.0,80.0);
		glColor3f(0.8,0.8,0.8);
		glRectf(21.0,21.0,79.0,79.0);


		glColor3f(0.196,0.196,0.8);
		glRectf(40,5,60,10);
		glColor3f(0.8,0.8,0.8);
		glRectf(40.5,5.5,59.5,9.5);

		glColor3f(0.137,0.137,0.556);
		drawString(46,6,0,GLUT_BITMAP_TIMES_ROMAN_24,"BACK");

		glColor3f(0.137,0.137,0.556);
		drawString(37,75,0,GLUT_BITMAP_TIMES_ROMAN_24,"HOW TO PLAY");
		drawString(23,69,0,GLUT_BITMAP_HELVETICA_18,"- Click and hold mouse left key to gain altitude of ");
		drawString(23,65,0,GLUT_BITMAP_HELVETICA_18,"    the plane.");
		drawString(23,61,0,GLUT_BITMAP_HELVETICA_18,"- Release the mouse left key to reduce the altitude.");
		drawString(23,57,0,GLUT_BITMAP_HELVETICA_18,"- Use the Right mouse key to speed up the plane(NOS)");
		drawString(23,53,0,GLUT_BITMAP_HELVETICA_18,"- Main aim of the game is to avoid the obstacles ");
		drawString(23,49,0,GLUT_BITMAP_HELVETICA_18,"    such as buildings and clouds.");
		drawString(23,45,0,GLUT_BITMAP_HELVETICA_18,"- Also the meter at the bottom shows the distance ");
		drawString(23,41,0,GLUT_BITMAP_HELVETICA_18,"    travelled,NITROS left,Atitude and the LEVEL.");
		drawString(23,37,0,GLUT_BITMAP_HELVETICA_18,"- As you reach distance multples of 50 tour level ");
		drawString(23,33,0,GLUT_BITMAP_HELVETICA_18,"    increases as well as the speed of the plane.");
		drawString(33,27,0,GLUT_BITMAP_HELVETICA_18," ENJOY PLAYING THE GAME");

		glutPostRedisplay();
	}
	else if (instflag == true)
	{
		glColor3f(0.3,0.56,0.84);   // background
		glBegin(GL_POLYGON);
		glVertex3f(0.0,0.0,0.0);
		glColor3f(0.137,0.137,0.556);
		glVertex3f(100.0,0.0,0.0);
		glColor3f(0.196,0.196,0.8);
		glVertex3f(100.0,100.0,0.0);
		glVertex3f(0.0,100.0,0.0);
		glEnd();
		glPushMatrix();
		glScalef(0.8,0.8,0);
		glPopMatrix();
		glColor3f(0.137,0.137,0.556);
		glRectf(20.0,20.0,80.0,80.0);
		glColor3f(0.8,0.8,0.8);
		glRectf(21.0,21.0,79.0,79.0);


		glColor3f(0.196,0.196,0.8);
		glRectf(40,5,60,10);
		glColor3f(0.8,0.8,0.8);
		glRectf(40.5,5.5,59.5,9.5);

		glColor3f(0.137,0.137,0.556);
		drawString(46,6,0,GLUT_BITMAP_TIMES_ROMAN_24,"BACK");

		glColor3f(0.137,0.137,0.556);
		drawString(37,75,0,GLUT_BITMAP_TIMES_ROMAN_24,"HOW TO PLAY");
		drawString(23,69,0,GLUT_BITMAP_HELVETICA_18,"- Click and hold mouse left key to gain altitude of ");
		drawString(23,65,0,GLUT_BITMAP_HELVETICA_18,"    the plane.");
		drawString(23,61,0,GLUT_BITMAP_HELVETICA_18,"- Release the mouse left key to reduce the altitude.");
		drawString(23,57,0,GLUT_BITMAP_HELVETICA_18,"- Use the Right mouse key to speed up the plane(NOS)");
		drawString(23,53,0,GLUT_BITMAP_HELVETICA_18,"- Main aim of the game is to avoid the obstacles ");
		drawString(23,49,0,GLUT_BITMAP_HELVETICA_18,"    such as buildings and clouds.");
		drawString(23,45,0,GLUT_BITMAP_HELVETICA_18,"- Also the meter at the bottom shows the distance ");
		drawString(23,41,0,GLUT_BITMAP_HELVETICA_18,"    travelled,NITROS left,Atitude and the LEVEL.");
		drawString(23,37,0,GLUT_BITMAP_HELVETICA_18,"- As you reach distance multples of 50 tour level ");
		drawString(23,33,0,GLUT_BITMAP_HELVETICA_18,"    increases as well as the speed of the plane.");
		drawString(33,27,0,GLUT_BITMAP_HELVETICA_18," ENJOY PLAYING THE GAME");

		glutPostRedisplay();

	}
	else
	{
		glPushMatrix();
		glScalef(0.8,0.8,0);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.196,0.196,0.8);
		glRectf(35.0,40.0,65.0,60.0);
		glColor3f(0.8,0.8,0.8);
		glRectf(36.0,41.0,64.0,59.0);
		glPopMatrix();
		glColor3f(0.137,0.137,0.556);
	    drawString(40,55,0,GLUT_BITMAP_HELVETICA_18," GAME PAUSED");
		drawString(37,45,0,GLUT_BITMAP_HELVETICA_18," PRESS 'P' to continue");
		glutPostRedisplay();

	}
	glFlush();*/
	glutSwapBuffers();
}


/* Call back when the windows is re-sized */
/*
void myReshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();
   if (width >= height) {
     // aspect >= 1, set the height from -1 to 1, with larger width
      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {
      // aspect < 1, set the width to -1 to 1, with larger height
     gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
}
*/

void myReshape(int w, int h)
{
	SCREENH=h,SCREENW=w;
	printf("width = %d\theight= %d",w,h);
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0,	-5.0 , 10.0);
	glMatrixMode(GL_MODELVIEW);
}

/* Called back when the timer expired */
/*void Timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, Timer, 0); // next Timer call milliseconds later
}*/

/* Callback handler for normal-key event */
void keyboard(unsigned char key, int x, int y) {
	/*
	if(key == 27)
	{
		exit(0);
	}
	else if(key == 'p' || key == 'P')
	{
		if(pause == true)
			pause = false;
		else
			pause = true;
	}*/
	//glutPostRedisplay();
	    switch (key) {
        case 101:   // вверх
            dir = 0;
            break;
        case 102:   // направо
            dir = 2;
            break;
        case 100:   // налево
            dir = 1;
            break;
        case 103:   // вниз
            dir = 3;
            break;
        case 27:    // Escape
            exit(0);
            break;
    }
}

/* Callback handler for mouse event */
/*
void mouse(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { // Pause/resume
      pause = !pause;         // Toggle state
      if (pause) {
         xSpeedSaved = xSpeed;  // Save parameters for restore later
         ySpeedSaved = ySpeed;
         xSpeed = 0;            // Stop movement
         ySpeed = 0;
      } else {
         xSpeed = xSpeedSaved;  // Restore parameters
         ySpeed = ySpeedSaved;
      }
   }
}*/

void fjfjfh()
{
    for(int i = 0; i < 2; i++)
        m[i].New();
    for(int i = 0; i < 10; i++)
        u[i].New();

    s[0].x = 25;
    s[0].y = 15;
}

void mouse(int button, int state, int ax, int ay)            // takes input from mouse
{
	int mx=ax*100/SCREENW,my=(SCREENH-ay)*100/SCREENH;		// m = mouse cordinate to graphics
	down= button==GLUT_LEFT_BUTTON && state==GLUT_LEFT;
	if(down)
    {
        if (key1==3)
        {
            if(mx > (40) && mx < (60) && my > (10) && my < (15) )
            {
                exit(0);
            }
            if(mx > (40) && mx < (60) && my > (20) && my < (25) )
            {
                d = 1;
                glClear(GL_COLOR_BUFFER_BIT);
                fjfjfh();
                key1=4;
                display();
            }
            if(mx > (40) && mx < (60) && my > (40) && my < (45) )
            {
                key1 = 1;
                d = 2;
                num = 5;
                Score = 0;
                fjfjfh();
                display();
            }
			if(mx > (40) && mx < (60) && my > (30) && my < (35) )
            {
                key1 = 2;
                d = 2;
                num = 5;
                Score = 0;
                fjfjfh();
                display();
            }
        }
        if (key1==4)
        {
            if(mx > (40) && mx < (60) && my > (5) && my < (10) )
            {
                key1=3;
                d = 1;
                glClear(GL_COLOR_BUFFER_BIT);
                fjfjfh();
                welcome();
            }
        }
    }
    glutMouseFunc(mouse);
	/*		mouse calculation//converting to screen coordinates-ortho values
	
	SCREENSIZE  ---->  ORTHO
	x(reqd val) ---->  ???
	*/
	/*if(instflag)
	{
		if(mx>40 && mx<60)
		{
			if(my>5 && my<10)
			{
				wflag = true;
				if(instflag)
					instflag = false;
			}
		}
	}
	if(wflag == true)
	{
		if(mx>40 && mx<60)
		{
			if(my>40 && my<45)
			{
				//start = true;
				wflag=false;
			}
			else if(my>30 && my<35)
			{
				//instflag = true;
				wflag = false;
			}
			else if(my>20 && my<25)
			{
				instflag = true;
				wflag = false;
			}
			else if(my>10 && my<15)
			{
				exit(0);
			}

		}
	}*/
}

void timer (int = 0)
{
    if (d==2){
        display();
    }
    Tick();

    glutTimerFunc (80,timer,0);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    srand(time(NULL));// Set random variable as current time
    net = new neural(num_inputs, num_outputs, num_layers, 10, learning_rate); //Send neural with initial values

    glutInit(&argc, argv);                 // Initialize GLUT

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Use RGBA color, enable double buffering and enable depth buffer
    glutInitWindowSize (SCREENW,SCREENH);  // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow("Srijana: User and Neural Network game"); // Create a window with the given title

    initGL();

    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutReshapeFunc(myReshape);       // Register callback handler for window re-size event
    glutTimerFunc (80,timer,0);     // First timer call immediately

    glutMouseFunc(mouse);   // Register callback handler for mouse event
    glutMainLoop();           // Enter the event-processing loop
    glutKeyboardFunc(keyboard);   // Register callback handler for special-key event
    return 0;
}