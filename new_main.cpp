#include<stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

int SCREENH=600,SCREENW=800;

int main (int argc,char **argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (SCREENW,SCREENH);

    
    CreateGlutWindow();
    glutDisplayFunc (display);
    glutTimerFunc (80,timer,0);
    glutSpecialFunc (MyKeyboard);
    glutMouseFunc(MousePressed);

    return 0;
}