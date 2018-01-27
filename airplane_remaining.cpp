

//#include<windows.h>







//---------------- Obstacles declaration----------



//-------------------declarations---------------

bool pause=false,wflag = true;//flags

//plane bounds



//-------------function prototypes------------------
void keyPressed(unsigned char,int,int);
void mouse(int button, int state, int x, int y);
void printString(float x,float y,float z,void *font,char *string);//what does this do??
void buildingBlock();
void CloudBlock();
void init();
void drawJet();
void gameEnd();
void drawBg();
void welcome();
void drawBuilding();
void drawCloud();
bool cloudHit();
bool buildingHit();
void printScore();
void display();
void moveJetU();
void moveJetD();



void semiCircle(float p1,float q1,float radius)
{
	float p,q;
	float angle;
	glBegin(GL_POINTS);

	for (angle=1.0f;angle<360.0f;angle++)
	{
		p = p1+sin(angle)*radius;
		q = q1+cos(angle)*radius;
		if(q>=100)
		glVertex2f(p,q);
	}
	glEnd();

}


void Circle(float x1,float y1,float radius)
{
	float x2,y2;
	float angle;
	glBegin(GL_POINTS);

	for (angle=1.0f;angle<360.0f;angle++)
	{
		x2 = x1+sin(angle)*radius;
		y2 = y1+cos(angle)*radius;
		glVertex2f(x2,y2);
	}
	glEnd();

}
