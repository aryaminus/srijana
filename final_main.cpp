/*
 * final_main.cpp: OpenGL/GLUT C/C++ Setup graphics project
 * To compile with -lfreeglut -lglu32 -lopengl32
 */

//http://www3.ntu.edu.sg/home/ehchua/programming/opengl/cg_introduction.html -> main reference

//#include <windows.h>  // for MS Windows
#include<stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include<time.h>
#include<stdio.h>
#include<math.h>

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
/*
GLfloat xSpeed = 0.02f;      // Ball's speed in x and y directions
GLfloat ySpeed = 0.007f;
int refreshMills = 30;      // Refresh period in milliseconds
bool pause=false;        // Movement paused or resumed
GLfloat xSpeedSaved, ySpeedSaved;  // To support resume
*/

#define BLOCKSPEED 0.09

#define BOOSTER_MAX 50

int SCREENH=600,SCREENW=800;

typedef struct building
{
	float block_x,block_y;

	bool state;
	int no_floors;
}building;

typedef struct Cloud
{
	float block_x,block_y;
	bool state;
}Cloud;

//building b;  // building struct
//int level=1,buildColor;  
//Cloud s;     // cloud struct

float bspd=BLOCKSPEED;  // block speed
bool pause=false,wflag = true,instflag=false,uflag=false,nflag=false;  //flags
float plane_mvmt=0.0;//jet movement up or down
float score=1;
char score_Str[20],slevel[20];   //score string and levelstring
int level=1,buildColor;     // initial level=1
building b;  // building struct
Cloud s;     // cloud struct
float booster=BOOSTER_MAX,boost=0;

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
	//GameOver Checking
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
	glFlush();
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
	}
	glutPostRedisplay();
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
void mouse(int button, int state, int x, int y)            // takes input from mouse
{
	int mx=x*100/SCREENW,my=(SCREENH-y)*100/SCREENH;		// m = mouse cordinate to graphics

	/*		mouse calculation//converting to screen coordinates-ortho values

	SCREENSIZE  ---->  ORTHO
	x(reqd val) ---->  ???
	*/
	if(instflag)
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
	}
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // Initialize GLUT

   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Use RGBA color, enable double buffering and enable depth buffer
   glutInitWindowSize (SCREENW,SCREENH);  // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow("Srijana: User and Neural Network game"); // Create a window with the given title
   
   initGL();

   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutReshapeFunc(myReshape);       // Register callback handler for window re-size event
   //glutTimerFunc(0, Timer, 0);     // First timer call immediately

   glutMouseFunc(mouse);   // Register callback handler for mouse event
   glutMainLoop();           // Enter the event-processing loop
   glutKeyboardFunc(keyboard);   // Register callback handler for special-key event
   return 0;
}