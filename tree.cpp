
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

//GLfloat r1, r2;
GLUquadric *q;
GLint n = 1;

int numOfBranches = 0;
float branchSize[] = { 5, 2, 1 };
static int counter = 0;
void Init(void)
{
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

	//glColor3ub(0, 0, 0);

		//glPushMatrix();
					  //glTranslatef(-1.1, 0, 0);
		/*glRotatef(120, 1, 1, 1);
		//glPushMatrix();
		//glRotatef(r1, 0, 0, 1); //rotate the main segment
		glTranslatef(0.5, 0, 0); //translate it to the origin
		glScalef(0.5, 0.1, 0.1); //scale it
		glutWireCube(1.f);  //make the cube
		glScalef(1, 10, 10);  //scale it back

		glTranslatef(0.5, 0, 0); //translate it to the end
		glRotatef(45, 1, 1, 1);   //rotate the second segment
		glTranslatef(0.5, 0, 0); //translate it to the origin
		glScalef(1, 0.1, 0.1); //scale 
		glutWireCube(1.f);  //and display
		glPopMatrix();

		
		glPushMatrix();
		glLoadIdentity(); //reset
		//glTranslatef(-1.1, 0, 0);
		glRotatef(120, 1, 1, 1);
		glTranslatef(0.5, 0, 0); //translate it to the origin
		glScalef(0.5, 0.1, 0.1); //scale it
		//glutWireCube(1.f);  //make the cube
		glScalef(1, 10, 10);  //scale it back

		glTranslatef(0.5, 0, 0); //translate it to the end
		glRotatef(-45, 1, 1, 1); //rotate the second segment
		glTranslatef(0.5, 0, 0); //translate it to the origin
		glScalef(1, 0.1, 0.1); //scale 
		glutWireCube(1.f);  //and display
		glPopMatrix();

	//r1 += 1.1;
	//r2 += 0;*/

	if (numOfBranches != 7)
	{
		counter++;
		if (counter == 100)
		{
			numOfBranches += 1; 
			counter = 0;
		}
		
		//counter ++ or counter --
		//if -- if counter == 0
		//numof branches += 1 and counter = max
		//if ++ counter == max
		//num branches += 1 and counter = 0
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

/*void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '+':
		for (int i = 0; i < 3; i++)
		{
			branchSize[i] = (float)rand() / RAND_MAX*.5 + 1;
			printf("%f\n", branchSize[i]);
		}
			
		//glutPostRedisplay();
		break;
	case '-':
		///glutPostRedisplay();
		n--;
		if (n < 1) {
			n = 1;
		}
		break;
		/*case 'y':
		glutPostRedisplay();
		break;
		case 'Y':
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
	printf("N=%i\n", n);
}*/

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
