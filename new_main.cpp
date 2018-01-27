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

int key1 = 3;

int num = 7;

char sScore[15];
int Score = 0;
char sHightScore[15];
int hightScore;

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

struct
{
    int x;
    int y;
} s[100];

void DrawSnake()
{
    glColor3f (0.0,1.0,0.0);
    for (int i = 0; i < num; i++)
    {
        glRectf (s[i].x*Scale, s[i].y*Scale, (s[i].x+1)*Scale, (s[i].y+1)*Scale);
    }
}

void draw_string(void *font, const char* string)
{
    while(*string)
        glutStrokeCharacter(font, *string++);
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

    //ifstream inFile("Snake.bin",ios_base::binary);

    /*while(inFile.peek()!=EOF)
        inFile >> sHightScore;
    inFile.close();*/
    
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

void display()
{
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
            DrawMenu();
            break;
        case 4:
            DrawRules();
            break;
    }
    glFlush();
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