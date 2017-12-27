
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

GLUquadric *q;
GLint n = 1;


int numOfBranches = 0; //starting value; will increase
float branchSize[] = { 5, 2, 1 };  //set size of branches called in an array
static int counter = 0;  //counter corresponds to time
void Init(void)
{
	//this creates the initial cylinder shape
	glClearColor(1, 1, 1, 1);
	glShadeModel(GL_FLAT);
	q = gluNewQuadric();
	glNewList(1, GL_COMPILE);
	gluCylinder(q, 1.f, 1.f, 1.f, 5.f, 5.f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEndList();
}

void Display(void)
{
	
}

void oneBranching(int numBranches,float branchSize[], int index = 0)
{

	glColor3ub(0, 0, 0);
	glPushMatrix();
	//branchSize = rand() / RAND_MAX*0.5 + 1;
	//branchSize /= 2;
	
	glScalef(.1, .1, branchSize[index]);
	glCallList(1);
	glPopMatrix();
	glTranslatef(0, 0, branchSize[index]);// Translate lower branches
	//Keep Going until 0
	if (numBranches == 0) return;
	glPushMatrix();
	glRotatef(-40* (float) rand() / RAND_MAX, 1, 0, 0);
	glRotatef(40* (float)rand() / RAND_MAX, 0, 0, 1);
	oneBranching(numBranches - 1, branchSize, 1);//Make 2nd Branch
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(40* (float)rand() / RAND_MAX, 1, 0, 0);
	glRotatef(-40* (float)rand() / RAND_MAX, 0, 0, 1);
	oneBranching(numBranches - 1,branchSize, 2);//Make 3rd Branch
	glPopMatrix();
}

void Idle(void) //only makes stump
{

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, -1,0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glScalef(0.1, 0.1, 0.1);

	if (numOfBranches != 7)
	{
		counter++;
		if (counter == 100)
		{
			numOfBranches += 1; 
			counter = 0;
		}
		
	}
	srand(2);
	oneBranching(numOfBranches, branchSize);// Call branching here
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(10, 10, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	Init();
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutReshapeFunc(Reshape);
	//glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}
