#include <gl\glut.h>
#include <math.h>
GLfloat angle = 0;
GLfloat moveX = 2;
GLfloat moveY = 2;
GLfloat moveZ = 2;

void zoomView()
{
	moveX += 0.05;
	moveY += 0.05;
	moveZ += 0.05;
}

void alienateView()
{
	moveX -= 0.05;
	moveY -= 0.05;
	moveZ -= 0.05;
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 120:
		{
			alienateView();
			break;
		}
		case 121:
		{
			zoomView();
			break;
		}

		default:
			break;
	}
}

void keyboardSpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
	{
		angle -= 2;
		if (angle > 360.0) angle = 0;

		break;
	}
	case GLUT_KEY_RIGHT:
	{
		angle += 2;
		if (angle > 360.0) angle = 0;
		break;
	}

	default:
		break;
	}
}

void init(void)
{
	glClearColor(0.9, 0.9, 0.9, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void myDisplay()
{
	glPushMatrix(); //Сохраняем VM = 1
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	gluLookAt(moveX, moveY, moveZ, 0, 0, 0, 0, 1, 0); // VM=Fwe
	GLfloat myLightPosition[] = { 3.0, 3.0, 3.0, 1.0 }; // Источник света в CKw
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition); /*Позиция источника света будет преобразована в CKe*/
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPushMatrix(); //Сохраняем VM=Fwe
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glRotatef(angle, 1, 0, 0); // VM=Fwe*R
	glutSolidCone(0.3, 0.7, 150, 150);



	glPopMatrix(); // Восстанавливаем VM=Fwe
	glDisable(GL_LIGHTING); //Выключаем освещение
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(-1.5, 0, 0); glVertex3f(1.5, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, -1.5, 0); glVertex3f(0, 1.5, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, -1.5); glVertex3f(0, 0, 1.5);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1, 1, 1); glVertex3f(3, 3, 3); glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}
void myReshape(int width, int height)
{
	if (width / height < 1) glViewport(0, 0, width, width);
	else glViewport(0, 0, height, height);
}


void myIdle()
{
	//angle += 0.5;
	//if (angle > 360.0) angle = 0;
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("my window");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutIdleFunc(myIdle);
	init();
	glutMainLoop();
}
