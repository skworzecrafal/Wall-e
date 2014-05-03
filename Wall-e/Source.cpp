#include <stdlib.h>
#include <GL\glut.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include <Windows.h>
#include "robot.h"
#include "Robo_AI.h"
#include "glWrap.h"
#include "Vector3.h"

char path[] = "C:\\Users\\marci_000\\Desktop\\MATLAB\\Robot Scripts\\DodgeSug.fis";
double *ret;

int obrotL = 0;
int obrotR = 0;
int kierunek = 0;
int krokL = 0;
int krokR = 0;
// aspekt obrazu

int aspect = 1;


// rozmiary bry³y obcinania

const GLdouble left = -50.0;
const GLdouble right = 50.0;
const GLdouble bottom = -50.0;
const GLdouble top = 50.0;
const GLdouble Near = 250.0;
const GLdouble Far = 350.0;

// wspó³czynnik skalowania

GLfloat scale = 1.0;

// k¹ty obrotu

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;
GLfloat transx=0, transy=0, transz=0;
int old_x=0;
int old_y=0;
int valid =0;

// funkcja generuj¹ca scenê 3D


void Display()
{
	// kolor t³a - zawartoœæ bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	//glEnable(GL_CULL_FACE);

	// przesuniêcie uk³adu wspó³rzêdnych obiektu do œrodka bry³y odcinania
	glTranslatef(0, 0, -(Near + Far) / 2);

	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, scale, scale);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// obroty obiektu - klawisze kursora
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);

	// kolor krawêdzi obiektu
	glColor3f(0.0, 0.0, 0.0);

	//glPolygonMode(GL_BACK, GL_LINE);
	// TU RYSOWAC::


	glWrap::Axis();
	glTranslatef(transx, transy, transz);
	robot(obrotL, obrotR);
	glWrap::LineOfPoints(Vector3f(0, 0, 10), Vector3f(0, 10, 0));
	


	// skierowanie poleceñ do wykonania
	glFlush();

	// zamiana buforów koloru
	glutSwapBuffers();
}


void CALLBACK Projekcja(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
	if (krokL >= 0)
	{
		obrotL += krokL;
		if (obrotL > 31)
			obrotL = obrotL % 32;
	}
	else
	{
		obrotL += krokL;
		if (obrotL < 0)
			obrotL = 31 + obrotL;
	}
	if (krokR >= 0)
	{
		obrotR += krokR;
		if (obrotR > 31)
			obrotR = obrotR % 32;
	}
	else
	{
		obrotR += krokR;
		if (obrotR < 0)
			obrotR = 31 + obrotR;
	}
	Display();
}
// zmiana wielkoœci okna
void Reshape(int width, int height)
{
	
	// obszar renderingu - ca³e okno
	glViewport(0, 0, width, height);

	// wybór macierzy rzutowania
	glMatrixMode(GL_PROJECTION);

	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();

	// parametry bry³y obcinania
	if (aspect == 1)
	{
		// wysokoœæ okna wiêksza od wysokoœci okna
		if (width < height && width > 0)
			glFrustum(left, right, bottom * height / width, top * height / width, Near, Far);
		else

			// szerokoœæ okna wiêksza lub równa wysokoœci okna
		if (width >= height && height > 0)
			glFrustum(left * width / height, right * width / height, bottom, top, Near, Far);

	}
	else
		glFrustum(left, right, bottom, top, Near, Far);
	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);
	
}
// obs³uga klawiatury r
void Keyboard(unsigned char key, int x, int y)
{
	// klawisz +
	if (key == '+')
		scale += 0.1;
	else

		// klawisz -
	if (key == '-' && scale > 0.1)
		scale -= 0.1;

	if (key == 'q')
	{
		if (krokL != 10)
		{
			krokL ++;
		}
	}

	if (key == 'a')
	{
		if (krokL !=-10)
		{
			krokL--;
		}
		
	}

	if (key == 'z')
	{
		if (krokL > 0)
			krokL--;
		if (krokL < 0)
			krokL++;
	}
	if (key == 'w')
	{
		if (krokR != 10)
		{
			krokR++;
		}
	}

	if (key == 's')
	{
		if (krokR != -10)
		{
			krokR--;
		}

	}

	if (key == 'x')
	{
		if (krokR > 0)
			krokR--;
		if (krokR < 0)
			krokR++;
	}
		
	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
// obs³uga klawiszy funkcyjnych i klawiszy kursora
void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		// kursor w lewo
	case GLUT_KEY_LEFT:
		rotatey -= 3;
		break;

		// kursor w prawo
	case GLUT_KEY_RIGHT:
		rotatey += 3;
		break;

		// kursor w górê
	case GLUT_KEY_UP:
		rotatex -= 3;
		break;

	

		// kursor w dó³
	case GLUT_KEY_DOWN:
		rotatex += 3;
		break;
	}

	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
void Mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		old_x = x;
		old_y = y;
		valid = GLUT_UP;
		break;
	case GLUT_RIGHT_BUTTON :
		break;
	case GLUT_MIDDLE_BUTTON :
		break;
	default:
		break;
	}
}
void ActiveMouse(int x, int y)
{
	if (valid) {
		
		int dx = old_x - x;
		int dy = old_y - y;
		rotatex -= dy/2;
		rotatey -= dx/2;
		/* do something with dx and dy */
	}
	old_x = x;
	old_y = y;
}
int main(int argc, char * argv[])
{
	////////////////////
	mclInitializeApplication(NULL, 0);
	RobotSI1Initialize();
	/////////////////////////////  

	
	//ret = Robo_AI::Dodge(0, 1023, 0, path);
	//std::cout << "left" << ret[0] << "right" << ret[1] << std::endl;
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);
	SetTimer(NULL, 1, 30, &Projekcja);
	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	// rozmiary g³ównego okna programu
	glutInitWindowSize(800, 600);
	
	// utworzenie g³ównego okna programu
	glutCreateWindow("WALL - e");



	// do³¹czenie funkcji generuj¹cej scenê 3D
	glutDisplayFunc(Display);

	// do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// do³¹czenie funkcji obs³ugi klawiatury
	glutKeyboardFunc(Keyboard);

	// do³¹czenie ob³ugi myszki
	glutMouseFunc(Mouse);
	glutMotionFunc(ActiveMouse);
	// do³¹czenie funkcji obs³ugi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc(SpecialKeys);

	// wprowadzenie programu do obs³ugi pêtli komunikatów
	glutMainLoop();
	KillTimer(NULL, 1);
	///////////////////////////
	RobotSI1Terminate();
	mclTerminateApplication();
	///////////////////////////
	return 0;
}