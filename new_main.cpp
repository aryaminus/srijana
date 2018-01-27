#include <iostream>
#include <fstream>

#include<time.h>
#include "math.h"

#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

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

int d = 1;

int dir;
bool down=false;

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


void DrawMenu()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON); // User
    glColor3f (0.0, 0.26, 0.0);
    glVertex3f (705.0, 650.0, 0.0);
    glColor3f (0.0, 0.19, 0.0);
    glVertex3f (500.0, 650.0, 0.0);
    glColor3f (0.0, 0.16, 0.0);
    glVertex3f (500.0, 550.0, 0.0);
    glColor3f (0.0, 0.19, 0.0);
    glVertex3f (705.0, 550.0, 0.0);
    glEnd();
    glBegin(GL_POLYGON); // Neural Network
    glColor3f (0.0, 0.26, 0.0);
    glVertex3f (805.0, 510.0, 0.0);
    glColor3f (0.0, 0.19, 0.0);
    glVertex3f (300.0, 510.0, 0.0);
    glColor3f (0.0, 0.16, 0.0);
    glVertex3f (300.0, 410.0, 0.0);
    glColor3f (0.0, 0.19, 0.0);
    glVertex3f (805.0, 410.0, 0.0);
    glEnd();
    glBegin(GL_POLYGON); // Exit
    glColor3f (0.0, 0.26, 0.0);
    glVertex3f (670.0, 230.0, 0.0);
    glColor3f (0.0, 0.19, 0.0);
    glVertex3f (540.0, 230.0, 0.0);
    glColor3f (0.0, 0.16, 0.0);
    glVertex3f (540.0, 140.0, 0.0);
    glColor3f (0.0, 0.19, 0.0);
    glVertex3f (670.0, 140.0, 0.0);
    glEnd();

    glLineWidth(4.0f);
    glColor3f (0.0,1.0,1.0);

    glPushMatrix();
    glTranslatef(w/(2.38), h/(1.3), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, "User");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(w/(3.38), h/(1.7), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, "Neural Network");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(w/(2.229), h/(4.4), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, "EXIT");
    glPopMatrix();

    glFinish();
    glutSwapBuffers();

}

void DrawRules()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glColor3f (0.0, 0.16, 0.0);
    glVertex3f (710.0, 150.0, 0.0);
    glColor3f (0.0, 0.19, 0.0);
    glVertex3f (490.0, 150.0, 0.0);
    glColor3f (0.0, 0.16, 0.0);
    glVertex3f (490.0, 90.0, 0.0);
    glColor3f (0.0, 0.19, 0.0);
    glVertex3f (710.0, 90.0, 0.0);
    glEnd();

    glLineWidth(1.8f);
    glColor3f (0.0,1.0,1.0);

    glPushMatrix();
    glTranslatef(w/3, h/(1.2), 0);
    glScalef(0.5f, 0.5f, 0.5f);
    draw_string(GLUT_STROKE_ROMAN, "How to play:");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(w/(3), h/(1.5), 0);
    glScalef(0.2f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "1.Eat fruit to score points:");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(w/(3), h/(1.7), 0);
    glScalef(0.2f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "2.Do not eat bombs:");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(w/(3), h/(2.0), 0);
    glScalef(0.2f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "3.Do not eat yourself.");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(w/(3), h/(2.4), 0);
    glScalef(0.2f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "4.Do not leave the window border.");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(w/(2.5), h/7, 0);
    glScalef(0.2f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "return to MENU");
    glPopMatrix();

    glLineWidth(3.0f);
    glColor3f (0.0,1.0,1.0);
    glPushMatrix();
    glTranslatef(w/(2.7), h/(3.3), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, "Good luck!");
    glPopMatrix();

    glColor3f (1.0, 1.0, 0.0);
    glRectf (780.0,500.0,805.0, 525.0);
    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for(float i=0; i < 2*3.14; i += 3.14/4)
    {
        glVertex2f(720.0 + (0.5)*Scale*(1.1)*sin(i), 450.0 + (0.5)*Scale*(1.1)*cos(i));
    }
    glEnd();

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

void Tick()
{
    for (int i = num; i > 0; --i)
    {
        s[i].x = s[i-1].x;
        s[i].y = s[i-1].y;
    }

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

    if (s[0].x > N || s[0].x < 0 || s[0].y > (M-3) || s[0].y < 0)
    {
        key1=2;
    }

    for (int i = 1; i < num; i++)
        if (s[0].x == s[i].x && s[0].y == s[i].y ){
            num = 3;
            if (Score > 0)
                Score-=3;
            if (Score < 0)
                Score = 0;
        }
}

void timer (int = 0)
{
    if (d==2){
        display();
    }
    Tick();

    glutTimerFunc (80,timer,0);
}

void MyKeyboard( int key, int a, int b)
{
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

void fjfjfh()
{
    for(int i = 0; i < 2; i++)
        m[i].New();
    for(int i = 0; i < 10; i++)
        u[i].New();

    s[0].x = 25;
    s[0].y = 15;
}

void MousePressed(int button, int state, int ax, int ay)
{
    down= button==GLUT_LEFT_BUTTON && state==GLUT_LEFT;
    if(down)
    {
        if (key1==3)
        {
            if(ax > (540.0) && ax < (670.0) && ay > (490.0) && ay < (600.0) )
            {
                exit(0);
            }
            if(ax > (500.0) && ax < (705.0) && ay > (230.0) && ay < (330.0) )
            {
                d = 1;
                glClear(GL_COLOR_BUFFER_BIT);
                fjfjfh();
                key1=4;
                display();
            }
            if(ax > (500.0) && ax < (705.0) && ay > (100.0) && ay < (190.0) )
            {
                key1 = 1;
                d = 2;
                num = 5;
                Score = 0;
                fjfjfh();
                display();
            }
        }
        if (key1==2)
        {
            if(ax > (580.0) && ax < (670.0) && ay > (660.0) && ay < (690.0) )
            {
                exit(0);
            }
            if(ax > (540.0) && ax < (670.0) && ay > (580.0) && ay < (610.0) )
            {
                key1=3;
                d = 1;
                glClear(GL_COLOR_BUFFER_BIT);
                fjfjfh();
                DrawMenu();
            }
        }
        if (key1==4)
        {
            if(ax > (520.0) && ax < (680.0) && ay > (580.0) && ay < (610.0) )
            {
                key1=3;
                d = 1;
                glClear(GL_COLOR_BUFFER_BIT);
                fjfjfh();
                DrawMenu();
            }
        }
    }
    glutMouseFunc(MousePressed);
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