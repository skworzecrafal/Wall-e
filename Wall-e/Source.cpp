#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <GL\glut.h>
#include <GL\GLU.h>
#include <GL\GL.h>
#include <Windows.h>
#include "PMath.h"
#include "robo.h"
#include "Robot.h"
#include "Robo_AI.h"
#include "glWrap.h"
#include "PMath.h"
#include "LoadOBJ.h"
#include "Obstacle.h"
#define BITMAP_ID 0x4D42


char path[] = "fis\\robotSugeno.fis";

double *ret;
GLuint textures[2];
Robot* a = new Robot();
enum{
	KAMERA_WIDOK_OGOLNY,
	KAMERA_PODAZANIE
};
int kamera = KAMERA_PODAZANIE;
vector<Obstacle> Obstancles;
float Vl = 0;
float Vr = 0;
int Hkat = 0;
int LhandV = 0;
int LhandH = 0;
int RhandV = 0;
int RhandH = 0;
float krokL = 0;
float krokR = 0;


// aspekt obrazu

int aspect = 1;


// rozmiary bry³y obcinania

const GLdouble Left = -50.0;
const GLdouble Right = 50.0;
const GLdouble bottom = -50.0;
const GLdouble top = 50.0;
const GLdouble Near =100.0;
const GLdouble Far = 1000.0;

// wspó³czynnik skalowania

GLfloat scale = 1.0;

// k¹ty obrotu

GLfloat rotatex = 20.0;
GLfloat rotatey = 0.0;
//GLfloat transx=0, transy=0, transz=0;
int old_x=0;
int old_y=0;
int valid =0;


GLdouble eyex = 0;
GLdouble eyey = 0;
GLdouble eyez = 0;

// wspó³rzêdne punktu w którego kierunku jest zwrócony obserwator,

GLdouble centerx = 0;
GLdouble centery = 0;
GLdouble centerz = -100;

// funkcja generuj¹ca scenê 3D
WFObject model;
const int ilosc = 9;
int walls[ilosc][5] = {
		{-210,0,-300,10,610},
		{200,0,-300,10,610},
		{-200,0,-300,400,10},
		{ -200, 0, 300, 400, 10 },
		{10,0,50,50,50},
		{115,0,35,50,30},
		{-80,0,-130,20,50},
		{65,0,211,50,30},
		{-150,0,98,20,50}
};
// LoadBitmapFile
// opis: ³aduje mapê bitow¹ z pliku i zwraca jej adres.
//       Wype³nia strukturê nag³ówka.
//	 Nie obs³uguje map 8-bitowych.
unsigned char *loadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;							// wskaŸnik pozycji pliku
	BITMAPFILEHEADER	bitmapFileHeader;		// nag³ówek pliku
	unsigned char		*bitmapImage;			// dane obrazu
	int					imageIdx = 0;		// licznik pikseli
	unsigned char		tempRGB;				// zmienna zamiany sk³adowych
	// otwiera plik w trybie "read binary"
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;
	// wczytuje nag³ówek pliku
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	// sprawdza, czy jest to plik formatu BMP
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}
	// wczytuje nag³ówek obrazu
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	// ustawia wskaŸnik pozycji pliku na pocz¹tku danych obrazu
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	// przydziela pamiêæ buforowi obrazu
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);
	// sprawdza, czy uda³o siê przydzieliæ pamiêæ
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}
	// wczytuje dane obrazu
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// sprawdza, czy dane zosta³y wczytane
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}
	// zamienia miejscami sk³adowe R i B 
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	// zamyka plik i zwraca wskaŸnik bufora zawieraj¹cego wczytany obraz
	fclose(filePtr);
	return bitmapImage;
}
GLuint LoadTexture(char * filename, const int numer)
{
	BITMAPINFOHEADER bitmapInfoHeader;
	GLubyte * data;

	data = loadBitmapFile(filename, &bitmapInfoHeader);

	glGenTextures(1, &textures[numer]);
	glBindTexture(GL_TEXTURE_2D, textures[numer]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return textures[numer];

}
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
void przeszkoda(Vector3f leftDown, int xSize, int zSize)
{
	int height = 60;

	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);

	glNormal3d(0, 0, 1);
	glTexCoord2f(0, 1); glVertex3f(leftDown.x, leftDown.y + height, leftDown.z + zSize);
	glTexCoord2f(0, 0); glVertex3f(leftDown.x, leftDown.y, leftDown.z + zSize);
	glTexCoord2f(1, 0); glVertex3f(leftDown.x + xSize, leftDown.y, leftDown.z + zSize);
	glTexCoord2f(1, 1); glVertex3f(leftDown.x + xSize, leftDown.y + height, leftDown.z + zSize);
	
	glNormal3d(1, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(leftDown.x + xSize, leftDown.y + height, leftDown.z + zSize);
	glTexCoord2f(0, 0); glVertex3f(leftDown.x + xSize, leftDown.y, leftDown.z + zSize);
	glTexCoord2f(1, 0); glVertex3f(leftDown.x + xSize, leftDown.y, leftDown.z);
	glTexCoord2f(1, 1); glVertex3f(leftDown.x + xSize, leftDown.y + height, leftDown.z);

	glNormal3d(0, 0, -1);
	glTexCoord2f(0, 1); glVertex3f(leftDown.x + xSize, leftDown.y + height, leftDown.z);
	glTexCoord2f(0, 0); glVertex3f(leftDown.x + xSize, leftDown.y, leftDown.z);
	glTexCoord2f(1, 0); glVertex3f(leftDown.x, leftDown.y, leftDown.z);
	glTexCoord2f(1, 1); glVertex3f(leftDown.x, leftDown.y + height, leftDown.z);

	glNormal3d(-1, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(leftDown.x, leftDown.y + height, leftDown.z);
	glTexCoord2f(0, 0); glVertex3f(leftDown.x, leftDown.y, leftDown.z);
	glTexCoord2f(1, 0); glVertex3f(leftDown.x, leftDown.y, leftDown.z + zSize);
	glTexCoord2f(1, 1); glVertex3f(leftDown.x, leftDown.y + height, leftDown.z + zSize);

	glNormal3d(0, 1, 0);
	glTexCoord2f(0, 1); glVertex3f(leftDown.x, leftDown.y + height, leftDown.z + zSize);
	glTexCoord2f(0, 0); glVertex3f(leftDown.x + xSize, leftDown.y + height, leftDown.z + zSize);
	glTexCoord2f(1, 0); glVertex3f(leftDown.x + xSize, leftDown.y + height, leftDown.z);
	glTexCoord2f(1, 1); glVertex3f(leftDown.x, leftDown.y + height, leftDown.z);

	glEnd();
}
void plansza()
{
	for (int i = 0; i < ilosc; i++)
		Obstancles.push_back(Obstacle(Vector3f(walls[i][0], walls[i][1], walls[i][2]), walls[i][3], walls[i][4]));
	/*Obstancles.push_back(Obstacle(Vector3f(200, 0, -300), 10, 610));
	Obstancles.push_back(Obstacle(Vector3f(-200, 0, -300), 400, 10));
	Obstancles.push_back(Obstacle(Vector3f(-200, 0, 300), 400, 10));
	Obstancles.push_back(Obstacle(Vector3f(10, 0, 50), 50, 50));
	Obstancles.push_back(Obstacle(Vector3f(115, 0, 35), 50, 30)); 
	Obstancles.push_back(Obstacle(Vector3f(-80, 0, -130), 20, 50));
	Obstancles.push_back(Obstacle(Vector3f(65, 0, 211), 50, 30));
	Obstancles.push_back(Obstacle(Vector3f(-150, 0, 98), 20, 50));*/
}

void Display()
{
	#pragma region
	// kolor t³a - zawartoœæ bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glMatrixMode(GL_MODELVIEW);
	
	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();
	
	//glEnable(GL_CULL_FACE);
	//init();
	// przesuniêcie uk³adu wspó³rzêdnych obiektu do œrodka bry³y odcinania
	glTranslatef(0, 0, -(Near +Far) / 2);
	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, scale, scale);
	
	if (kamera == KAMERA_PODAZANIE)
	{
		glTranslatef(0, 0, (Near + Far) / 2 - 150);
		glRotatef(rotatex, 1.0, 0, 0);
		glRotatef(rotatey, 0, 1.0, 0);
		glRotatef(-a->oldRot, 0, 1, 0);
		glTranslatef(-a->Center.x, -30, -a->Center.z);
	}
	if (kamera == KAMERA_WIDOK_OGOLNY)
	{
		glRotatef(rotatex, 1.0, 0, 0);
		glRotatef(rotatey, 0, 1.0, 0);
	}
	
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
	
	glEnable(GL_TEXTURE_2D);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	
	glBegin(GL_QUADS);
	
	glColor3ub(40, 40, 40);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 1);	glVertex3f(-200, 0, -300);
	glTexCoord2f(0, 0);	glVertex3f(-200, 0, 300);
	glTexCoord2f(1, 0);	glVertex3f(200, 0, 300);
	glTexCoord2f(1, 1);	glVertex3f(200, 0, -300);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, textures[1]);

	for (int i = 0; i < ilosc; i++)
		przeszkoda(Vector3f(walls[i][0], walls[i][1], walls[i][2]), walls[i][3], walls[i][4]);
	/*przeszkoda(Vector3f(10, 0, 50), 50, 50);
	przeszkoda(Vector3f(200, 0, -300), 10, 610);
	przeszkoda(Vector3f(65, 0, 211), 50, 30);
	przeszkoda(Vector3f(65, 0, 211), 50, 30);*/

	glDisable(GL_TEXTURE_2D);
	// kolor krawêdzi obiektu
	glColor3f(0.0, 0.0, 0.0);
#pragma endregion rozne roznosci
	// TU RYSOWAC::
	//glWrap::Axis();
	glPushMatrix();
	//glRotatef(180, 0, 1, 0);
	
#pragma region
	bool iSeeL = false;
	for (int i = 0; i < Obstancles.size(); i++)
	{
		for (int j = 0; j < a->laserPointsLeft.size(); j++)
		{
			if (Obstancles[i].Contain(a->laserPointsLeft[j]))
			{
				float x = PMath::Plength(a->laserPointsLeft[0], a->laserPointsLeft[j]);
				a->leftValue = PMath::GetEValue((float)x);
				//glWrap::Print(-30, 50, "Left: " + std::to_string(a->leftValue));
				iSeeL = true;
				break;

			}
			if (j == a->laserPointsLeft.size() - 1 && i == Obstancles.size() - 1)
			{
				a->leftValue = PMath::GetEValue((float)60);
				//glWrap::Print(-30, 50, "Left: " + std::to_string(a->leftValue));
				iSeeL = false;
			}
		}
		if (iSeeL)
			break;
	}
#pragma endregion leftSensor
#pragma region
	bool iSeeR = false;
	for (int i = 0; i < Obstancles.size(); i++)
	{
		for (int j = 0; j < a->laserPointsRight.size(); j++)
		{
			if (Obstancles[i].Contain(a->laserPointsRight[j]))
			{
				float x = PMath::Plength(a->laserPointsRight[0], a->laserPointsRight[j]);
				a->rightValue = PMath::GetEValue((float)x);
				//glWrap::Print(-30, 30, "Right: " + std::to_string(a->rightValue));
				iSeeR = true;
				break;

			}
			if (j == a->laserPointsRight.size() - 1 && i == Obstancles.size() - 1)
			{
				a->rightValue = PMath::GetEValue((float)60);
				//glWrap::Print(-30, 30, "Right: " + std::to_string(a->rightValue));
				iSeeR = false;
			}
			if (iSeeR)
				break;
		}
	}
#pragma endregion rightSensor
#pragma region 
	bool iSeeF = false;
	for (int i = 0; i < Obstancles.size(); i++)
	{
		for (int j = 0; j < a->laserPointsFront.size(); j++)
		{
			if (Obstancles[i].Contain(a->laserPointsFront[j]))
			{
				
				float x = PMath::Plength(a->laserPointsFront[0], a->laserPointsFront[j]);
				a->frontValue = PMath::GetEValue((float)x);
				//glWrap::Print(-30, 40, "Front: " + std::to_string(a->frontValue));
				iSeeF = true;
				break;

			}
			if (j == a->laserPointsFront.size() - 1 && i == Obstancles.size() - 1)
			{
				a->frontValue = PMath::GetEValue((float)60);
				//glWrap::Print(-30, 40, "Front: " + std::to_string(a->frontValue));
				iSeeF = false;
			}
			if (iSeeF)
				break;
		}
	}
#pragma endregion frontSensor
	vector<double> ret = Robo_AI::Dodge(a->leftValue, a->frontValue, a->rightValue, path);
	//glWrap::Print(30, 30, to_string(ret[0]) + "   " + to_string(ret[1]));
	Robo_AI::Movement(a, (float)ret[0]/10, (float)ret[1]/10);
	Vl += ret[0]/4;
	Vr += ret[1]/4;
	for (int i = 0; i < Obstancles.size(); i++)
		Obstancles[i].Draw();
	a->Rysuj(Vl, Vr, Hkat, LhandH, LhandV, RhandH, RhandV);
	glPopMatrix();
	//glutPostRedisplay();

	 //skierowanie poleceñ do wykonania
	glFlush();

	// zamiana buforów koloru
	glutSwapBuffers();

}


void CALLBACK Projekcja(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
	
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
		//	glFrustum(Left, Right, bottom * height / width, top * height / width, Near, Far);
		gluPerspective(30, (-Left + Right) / (top * height / width - bottom * height / width), Near, Far);
		else

		//	// szerokoœæ okna wiêksza lub równa wysokoœci okna
		if (width >= height && height > 0)
			//glFrustum(Left * width / height, Right * width / height, bottom, top, Near, Far);
			gluPerspective(30, (Right * width / height - Left * width / height)/(top-bottom), Near, Far);
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
		RhandH += 5;
		break;
	case 'f':
		RhandH -= 5;
		break;
	case 't':
		if (eyey < 15)
			eyey += 1;
		break;
	case 'g':
		if (eyey > -15)
			eyey -= 1;
		break;
	case 'y':
		if (eyez < 15)
			eyez += 1;
		break;
	case 'h':
		if (eyez > -15)
			eyez -= 1;
		break;
	case 'u':
		if (centerx < 15)
			centerx += 1;
		break;
	case 'j':
		if (centerx > -15)
			centerx -= 1;
		break;
	case 'i':
		if (centery < 15)
			centery += 1;
		break;
	case 'k':
		if (centery > -15)
			centery -= 1;
		break;
	case 'o':
		if (centerz < 120)
			centerz += 1;
		break;
	case 'l':
		if (centerz > 80)
			centerz -= 1;
		break;
	case '1':
		kamera = KAMERA_PODAZANIE;
		rotatex = 20;
		rotatey = 0;
		scale = 1;
		break;
	case '2':
		kamera = KAMERA_WIDOK_OGOLNY;
		rotatex = 30;
		rotatey -= 45;
		scale = 0.6;
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
		a->OriPosition = oRightWheel;
		break;
		// kursor w prawo
	case GLUT_KEY_RIGHT:
		a->OriPosition = oLeftWheel;
		break;
		// kursor w górê
	case GLUT_KEY_UP:
	//	Robo_AI::Movement(a, 0.827/4, 9.16/4);
		Robo_AI::Movement(a, -3,1);
		break;
		// kursor w dó³
	case GLUT_KEY_DOWN:
		Robo_AI::Movement(a, 3,3);
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


int main(int argc, char * argv[])
{
	
	

	////////////////////
	mclInitializeApplication(NULL, 0);
	RobotSI1Initialize();
	/////////////////////////////  


	//glWrap::LoadModel("obiekt");
	//model.load("wall-e elementy\\wallBody.obj");

	//double left =  Robo_AI::Dodge(0, 1023, 0, path)[0];
	//double right = Robo_AI::Dodge(0, 1023, 0, path)[1];
	//
	//std::cout << "left" << left << "right" << right << std::endl;
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);
	SetTimer(NULL, 1, 20, &Projekcja);
	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//init();
	// rozmiary g³ównego okna programu
	glutInitWindowSize(800, 600);
	
	// utworzenie g³ównego okna programu
	glutCreateWindow("WALL - e");


	LoadTexture("tekstury\\asfalt.bmp", 0);
	LoadTexture("tekstury\\s1.bmp", 1);
	plansza();
	
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
	delete a;
	return 0;
}