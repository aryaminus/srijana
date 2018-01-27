#include<stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

int SCREENH=600,SCREENW=800;

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

int main (int argc,char **argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (SCREENW,SCREENH);
    glutInitWindowPosition (50,50);
    glutCreateWindow ("Srijana");
    init();

    return 0;
}