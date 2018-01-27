#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

#include <GL/gl.h>
#include <GL/glut.h>

#define BLOCKSPEED 0.09

#define BOOSTER_MAX 50

int SCREENH=600,SCREENW=800;

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (SCREENW,SCREENH);
	glutInitWindowPosition (50,50);
	glutCreateWindow ("Airplane Escape!");
	return 0;

}