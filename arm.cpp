
#include <stdlib.h>
#include <GL/glut.h>

GLfloat r1,r2;


void Init(void) 
{
   glClearColor (1,1,1,1);
   glShadeModel (GL_FLAT);
}

void Display(void)
{

}



void Idle(void)
{

   glClear (GL_COLOR_BUFFER_BIT);
   glColor3ub(0,0,0);
   glLoadIdentity(); //reset
   glTranslatef(0.1,0,0);
   glRotatef(45,1,1,1);
   glPushMatrix();
   glRotatef(r1,0,0,1); //rotate the main segment
   glTranslatef(0.5,0,0); //translate it to the origin
   glScalef(1,0.1,0.1); //scale it
   glutWireCube(1.f);  //make the cube
   glScalef(1,10,10);  //scale it back
   glTranslatef(0.5,0,0); //translate it to the end
   glRotatef(r2,0,0,1);   //rotate the second segment
   glTranslatef(0.5,0,0); //translate it to the origin
   glScalef(1,0.1,0.1); //scale 
   glutWireCube(1.f);  //and display
   glPopMatrix();
   r1+=0.1;
   r2+=0.7;
   glutSwapBuffers();
}

void Reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(-2,2,-2,2,-20,20);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void Keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'd':
         glutPostRedisplay();
         break;
      case 'D':
         glutPostRedisplay();
         break;
      case 'y':
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
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (700, 700); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow(argv[0]);
   Init();
   glutDisplayFunc(Display); 
   glutIdleFunc(Idle); 
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(Keyboard);
   glutMainLoop();
   return 0;
}
