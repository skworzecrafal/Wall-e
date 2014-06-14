#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <GL\glut.h>
#include <GL/glext.h>
#include <Windows.h>
#include "PMath.h"
#include "robo.h"
#include "Robot.h"
#include "Robo_AI.h"
#include "glWrap.h"
#include "PMath.h"
#include "LoadOBJ.h"

PFNGLDRAWRANGEELEMENTSEXTPROC glDrawRangeElementsEXT = NULL;

char path[] = "C:\\Users\\marci_000\\Desktop\\MATLAB\\Robot Scripts\\DodgeSug.fis";
double *ret;

Robot* a = new Robot();


int Vl = 0;
int Vr = 0;
int Hkat = 0;
int LhandV = 0;
int LhandH = 0;
int RhandV = 0;
int RhandH = 0;
int krokL = 0;
int krokR = 0;


// aspekt obrazu

int aspect = 1;


// rozmiary bry³y obcinania

const GLdouble Left = -50.0;
const GLdouble Right = 50.0;
const GLdouble bottom = -50.0;
const GLdouble top = 50.0;
const GLdouble Near = 250.0;
const GLdouble Far = 550.0;

// wspó³czynnik skalowania

GLfloat scale = 1.0;

// k¹ty obrotu

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;
//GLfloat transx=0, transy=0, transz=0;
int old_x=0;
int old_y=0;
int valid =0;


GLdouble eyex = 0;
GLdouble eyey = 0;
GLdouble eyez = 3;

// wspó³rzêdne punktu w którego kierunku jest zwrócony obserwator,

GLdouble centerx = 0;
GLdouble centery = 0;
GLdouble centerz = 0;

// funkcja generuj¹ca scenê 3D
WFObject model;
void init()
{
	// Light values and coordinates
	GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat  diffuseLight[] = { 0.1f, 0.1f, 0.1f, 0.1f };
	GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat	 lightPos[] = { 0.0f, 30.0f, 70.0f, 0.0f };
	GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	  
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	//Enable lighting
	glEnable(GL_LIGHTING);

	//Setup and enable light 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	//Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	//Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity
	// with a high shine
	glMaterialfv(GL_FRONT, GL_DIFFUSE, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);


	// White background
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}
void Display()
{
	// kolor t³a - zawartoœæ bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glMatrixMode(GL_MODELVIEW);
	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, 0, 1, 0);
	//glEnable(GL_CULL_FACE);
	//init();
	// przesuniêcie uk³adu wspó³rzêdnych obiektu do œrodka bry³y odcinania
	glTranslatef(0, 0, -(Near + Far) / 2);

	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, scale, scale);

	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	// w³¹czenie oœwietlenia
	glEnable(GL_LIGHTING);

	// w³¹czenie œwiat³a GL_LIGHT0 z parametrami domyœlnymi
	glEnable(GL_LIGHT0);

	// w³¹czenie automatycznej normalizacji wektorów normalnych
	glEnable(GL_NORMALIZE);

	// w³¹czenie obs³ugi w³aœciwoœci materia³ów
	glEnable(GL_COLOR_MATERIAL);
	// obroty obiektu - klawisze kursora
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);
	
	// kolor krawêdzi obiektu
	glColor3f(0.0, 0.0, 0.0);
	
	// TU RYSOWAC::
	glWrap::Axis();
	a->Rysuj(Vl, Vr, Hkat, LhandH, LhandV, RhandH, RhandV);
	
	

	glWrap::Print(10, 50, "LW " + a->LeftWheel.ToString());
	glWrap::Print(10, 40, "RW " + a->RightWheel.ToString());
	glWrap::Print(10, 30, "C " + a->Center.ToString());
	//glutPostRedisplay();

	 //skierowanie poleceñ do wykonania
	glFlush();

	// zamiana buforów koloru
	glutSwapBuffers();

}


void CALLBACK Projekcja(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
	Vl += krokL;
	Vr += krokR;
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
			glFrustum(Left, Right, bottom * height / width, top * height / width, Near, Far);
		else

			// szerokoœæ okna wiêksza lub równa wysokoœci okna
		if (width >= height && height > 0)
			glFrustum(Left * width / height, Right * width / height, bottom, top, Near, Far);

	}
	else
		glFrustum(Left, Right, bottom, top, Near, Far);

	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);
	
}
// obs³uga klawiatury
void Keyboard(unsigned char key, int x, int y)
{
	// klawisz +
	if (key == '+')
		scale += 0.1;
	else

		// klawisz -
	if (key == '-' && scale > 0.1)
		scale -= 0.1;

	switch (key)
	{
	case 'w':
		a->Translation.z -= 1;
		break;
	case 's':
		a->Translation.z += 1;
		break;
	case 'a':
		a->Translation.x -= 1;
		break;
	case 'd':
		a->Translation.x += 1;
		break;
	case 'q':
		a->Rotation.y += 1;
		break;
	case 'e':
		a->Rotation.y -= 1;
		break;
	case 'r':
		if (krokL < 15)
			krokL += 1;
		break;
	case 'f':
		if (krokL > -15)
			krokL -= 1;
		break;
	case 't':
		if (krokR < 15)
			krokR += 1;
		break;
	case 'g':
		if (krokR > -15)
			krokR -= 1;
		break;
	case 'y':
		if (LhandV > -90)
			LhandV -= 1;
		break;
	case 'h':
		if (LhandV < 35)
			LhandV += 1;
		break;
	case 'u':
		if (RhandV > -90)
			RhandV -= 1;
		break;
	case 'j':
		if (RhandV < 35)
			RhandV += 1;
		break;
	case 'v':
		if (LhandH > -3)
			LhandH -= 1;
		break;
	case 'b':
		if (LhandH < 90)
			LhandH += 1;
		break;
	case 'n':
		if (RhandH > -90)
			RhandH -= 1;
		break;
	case 'm':
		if (RhandH < 3)
			RhandH += 1;
		break;
	case 'i':
		if (Hkat > -20)
			Hkat -= 1;
		break;
	case 'k':
		if (Hkat < 8)
			Hkat += 1;
		break;
	case 27 :
		exit(0);
	default:
		break;
	}
	//for (int i = 0; i < 9; i++)
		// odrysowanie okna
	/*std::cout << "DL"<<a->DownLeft.ToString() << '\n';
	std::cout <<"DR"<<a->DownRight.ToString() << '\n';
	std::cout << "UL"<< a->UpLeft.ToString() << '\n';
	std::cout <<"RU" <<a->UpRight.ToString() << '\n';*/

	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
// obs³uga klawiszy funkcyjnych i klawiszy kursora
void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		// kursor w lewo
	case GLUT_KEY_LEFT:
		a->OriPosition = oLeftWheel;
		break;
		// kursor w prawo
	case GLUT_KEY_RIGHT:
		a->OriPosition = oRightWheel;
		break;
		// kursor w górê
	case GLUT_KEY_UP:
		Robo_AI::Movement(a, 1, 3);
		break;
		// kursor w dó³
	case GLUT_KEY_DOWN:
		a->OriPosition = oCenter;
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
	case 3:
		scale += 0.03;
		break;
	case 4:
		scale -= 0.03;
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
		//eyex -= (dx/60.0);
		rotatex -= dy / 2;
		rotatey -= dx / 2;
		/* do something with dx and dy */
	}
	old_x = x;
	old_y = y;
}
void ExtensionSetup()
{
	// pobranie numeru wersji biblioteki OpenGL
	const char * version = (char *)glGetString(GL_VERSION);

	// odczyt wersji OpenGL
	int major = 0, minor = 0;
	if (sscanf(version, "%d.%d", &major, &minor) != 2)
	{
#ifdef WIN32
		printf("B³êdny format wersji OpenGL\n");
#else

		printf("Bledny format wersji OpenGL\n");
#endif

		exit(0);
	}

	// sprawdzenie czy jest co najmniej wersja 1.2
	if (major > 1 || minor >= 2)
	{
		// pobranie wskaŸników wybranych funkcji OpenGL 1.2
		glDrawRangeElementsEXT =
			(PFNGLDRAWRANGEELEMENTSEXTPROC)wglGetProcAddress("glDrawRangeElements");
	}
	else

		// sprawdzenie czy jest obs³ugiwane rozszerzenie EXT_draw_range_elements
		if (glutExtensionSupported("GL_EXT_draw_range_elements"))
		{
		// pobranie wskaŸników wybranych funkcji rozszerzenia EXT_draw_range_elements
		glDrawRangeElementsEXT =
			(PFNGLDRAWRANGEELEMENTSEXTPROC)wglGetProcAddress("glDrawRangeElementsEXT");
		}
		else
		{
			printf("Brak rozszerzenia EXT_draw_range_elements!\n");
			glDrawRangeElementsEXT = NULL;
		}
}
int main(int argc, char * argv[])
{
	////////////////////
	/*mclInitializeApplication(NULL, 0);
	RobotSI1Initialize();*/
	/////////////////////////////  
	//glWrap::LoadModel("obiekt");
	//model.load("wall-e elementy\\wallBody.obj");
	//ret = Robo_AI::Dodge(0, 1023, 0, path);
	//std::cout << "left" << ret[0] << "right" << ret[1] << std::endl;
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);
	SetTimer(NULL, 1, 30, &Projekcja);
	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//init();
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
	ExtensionSetup();
	// wprowadzenie programu do obs³ugi pêtli komunikatów
	glutMainLoop();
	KillTimer(NULL, 1);
	///////////////////////////
	//RobotSI1Terminate();
	//mclTerminateApplication();
	///////////////////////////
	delete a;
	return 0;
}