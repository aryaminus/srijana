#include<stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

int Scale = 25;

int N = 50,M = 30;
int w = Scale * N;
int h = Scale * M;

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

void CreateGlutWindow()
{
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition (50,50);
    glutInitWindowSize (w,h);
    glutCreateWindow ("Srijana");
    glClearColor(0.0, 0.18, 0.0, 0);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (0, w, 0, h);
}

int main (int argc,char **argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    CreateGlutWindow();
    
    glutDisplayFunc (display);
    glutTimerFunc (80,timer,0);
    glutSpecialFunc (MyKeyboard);
    glutMouseFunc(MousePressed);

    glutMainLoop(); 

    return 0;
}