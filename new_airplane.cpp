#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

#include <GL/gl.h>
#include <GL/glut.h>

#define BLOCKSPEED 0.09

#define BOOSTER_MAX 50

int SCREENH=600,SCREENW=800;
int buildColor; 

typedef struct building
{
	float block_x,block_y;

	bool state;
	int no_floors;
}building;

building b;

typedef struct Cloud
{
	float block_x,block_y;
	bool state;
}Cloud;

Cloud s;

void buildingBlock()
{
	b.block_x=50.0;
	srand(time(0));
	b.no_floors = rand()%3+4;
	buildColor = rand()%3;

	b.block_y=b.no_floors*10 +15;   // generate block y cordinate depending on no of floors
	b.state=true;
	s.state=false;

}

void init()
{
	srand(time(0));
	int random = rand()%2;
	if( random == 0)
	{
		buildingBlock();
	}
	else
	{
		CloudBlock();
	}


}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (SCREENW,SCREENH);
	glutInitWindowPosition (50,50);
	glutCreateWindow ("Airplane Escape!");
    init();
	return 0;

}