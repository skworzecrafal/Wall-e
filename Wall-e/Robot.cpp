#include "Robot.h"

#include <GL/glut.h>
#define M_PI 3.14
#define X 0
#define Y 1
enum {
	BODY,
	HEAD1,
	HEAD2,
	HEAD3,
	HEAD4,
	GASIENICA,
	LARGE_WHEEL,
	L_ARM,
	L_ARM_PIVOT,
	L_HAND,
	MEDIUM_WHEEL,
	NAPED_MOCOWANIE_1,
	NAPED_MOCOWANIE_2,
	R_ARM,
	R_ARM_PIVOT,
	R_HAND,
	SMALL_WHEEL
};
Robot::Robot()
{
	width = 10;
	lWheel = Vector3f(0, 0, -width / 2);
	rWheel = Vector3f(width, 0, -width / 2);
	center = Vector3f(width / 2, 0, -width / 2);
	model[BODY].load("wall-e elementy\\wallBody.txt");
	model[HEAD1].load("wall-e elementy\\wallHead1.txt");
	model[HEAD2].load("wall-e elementy\\wallHead2.txt");
	model[HEAD3].load("wall-e elementy\\wallHead3.txt");
	model[HEAD4].load("wall-e elementy\\wallHead4.txt");
	model[GASIENICA].load("wall-e elementy\\Gasienica.txt");
	model[LARGE_WHEEL].load("wall-e elementy\\LargeWheel.txt");
	model[L_ARM].load("wall-e elementy\\lArm.txt");
	model[L_ARM_PIVOT].load("wall-e elementy\\lArmPivot.txt");
	model[L_HAND].load("wall-e elementy\\lHand.txt");
	model[MEDIUM_WHEEL].load("wall-e elementy\\MediumWheel.txt");
	model[NAPED_MOCOWANIE_1].load("wall-e elementy\\NapedMocowanie1.txt");
	model[NAPED_MOCOWANIE_2].load("wall-e elementy\\NapedMocowanie2.txt");
	model[R_ARM].load("wall-e elementy\\rArm.txt");
	model[R_ARM_PIVOT].load("wall-e elementy\\rArmPivot.txt");
	model[R_HAND].load("wall-e elementy\\rHand.txt");
	model[SMALL_WHEEL].load("wall-e elementy\\SmallWheel.txt");
}
Robot::~Robot()
{
}

void Robot::gasienica(int obrot)
{
	float wspSr[3][2] = { { -10.0f, 1.0f },
	{ 10.0f, 1.0f },
	{ 0.0f, 7.0f } };
	float katy[4] = { 120, 60, 60, 120 };
	float wspPkt[4][2] = { { cos(katy[0] / 180.0 * M_PI) + wspSr[0][X], sin(katy[0] / 180.0 * M_PI) + wspSr[0][Y] },
	{ cos(katy[1] / 180.0 * M_PI) + wspSr[1][X], sin(katy[1] / 180.0 * M_PI) + wspSr[1][Y] },
	{ cos(katy[2] / 180.0 * M_PI) + wspSr[2][X], sin(katy[2] / 180.0 * M_PI) + wspSr[2][Y] },
	{ cos(katy[3] / 180.0 * M_PI) + wspSr[2][X], sin(katy[3] / 180.0 * M_PI) + wspSr[2][Y] } };

	float a[2] = { (wspPkt[2][Y] - wspPkt[1][Y]) / (wspPkt[2][X] - wspPkt[1][X]),
		(wspPkt[0][Y] - wspPkt[3][Y]) / (wspPkt[0][X] - wspPkt[3][X]) };

	float b[2] = { wspPkt[1][Y] - a[0] * wspPkt[1][X], wspPkt[3][Y] - a[1] * wspPkt[3][X] };

	float kat = 2.5;
	float skok = (wspSr[1][X] - wspSr[0][X]) / roundf((wspSr[1][X] - wspSr[0][X]) / (kat / 180.0 * M_PI));
	float ilosc = sqrtf(pow((wspPkt[2][Y] - wspPkt[1][Y]), 2) + pow((wspPkt[2][X] - wspPkt[1][X]), 2)) / skok;
	float skokUksos = (wspPkt[1][X] - wspPkt[2][X]) / ilosc;
	float grubosc = 1.5;
	//PRZOD:
	glColor3d(0.9, 0.3, 0);

	glBegin(GL_QUADS);
	glVertex3f(wspSr[0][X], 0.0f, 0.0f);
	glVertex3f(wspSr[1][X], 0.0f, 0.0f);
	glVertex3f(wspSr[1][X], wspSr[1][Y], 0.0f);
	glVertex3f(wspSr[0][X], wspSr[0][Y], 0.0f);

	glVertex3f(wspSr[1][X], wspSr[1][Y], 0.0f);
	glVertex3f(wspPkt[1][X], wspPkt[1][Y], 0.0f);
	glVertex3f(wspPkt[2][X], wspPkt[2][Y], 0.0f);
	glVertex3f(wspSr[2][X], wspSr[2][Y], 0.0f);

	glVertex3f(wspSr[2][X], wspSr[2][Y], 0.0f);
	glVertex3f(wspPkt[3][X], wspPkt[3][Y], 0.0f);
	glVertex3f(wspPkt[0][X], wspPkt[0][Y], 0.0f);
	glVertex3f(wspSr[0][X], wspSr[0][Y], 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(wspSr[0][X], wspSr[0][Y], 0.0f);
	glVertex3f(wspSr[1][X], wspSr[1][Y], 0.0f);
	glVertex3f(wspSr[2][X], wspSr[2][Y], 0.0f);
	glEnd();


	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(wspSr[1][X], wspSr[1][Y], 0.0f);
	float angle = -90.0;
	while (angle <= 60.0)
	{
		glVertex3f(cos(angle / 180.0f*3.14) + wspSr[1][X], sin(angle / 180.0f*3.14) + wspSr[1][Y], 0.0f);
		angle += kat;
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(wspSr[2][X], wspSr[2][Y], 0.0f);
	angle = 30.0;
	while (angle <= 120.0)
	{
		glVertex3f(cos(angle / 180.0f*3.14) + wspSr[2][X], sin(angle / 180.0f*3.14) + wspSr[2][Y], 0.0f);
		angle += kat;
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(wspSr[0][X], wspSr[0][Y], 0.0f);
	angle = 120.0;
	while (angle <= 270.0)
	{
		glVertex3f(cos(angle / 180.0f*3.14) + wspSr[0][X], sin(angle / 180.0f*3.14) + wspSr[0][Y], 0.0f);
		angle += kat;
	}
	glEnd();

	//TASMA:
	int liczKol = 16 - obrot;
	int color = 1;
	glColor3f(1.0, 0, 0);
	float wsp = wspSr[0][X];
	glBegin(GL_QUAD_STRIP);
	while (wsp <= wspSr[1][X])
	{
		if (color == 1 && liczKol == 16)
		{
			glColor3f(1, 0, 0);
			color = 0;
			liczKol = 0;
		}
		if (color == 0 && liczKol == 16)
		{
			glColor3f(0, 1, 0);
			color = 1;
			liczKol = 0;
		}
		glVertex3f(wsp, 0, 0);
		glVertex3f(wsp, 0, -grubosc);
		wsp += skok;
		liczKol++;
	}
	angle = -85;
	while (angle <= 60)
	{
		if (color == 1 && liczKol == 16)
		{
			glColor3f(1, 0, 0);
			color = 0;
			liczKol = 0;
		}
		if (color == 0 && liczKol == 16)
		{
			glColor3f(0, 1, 0);
			color = 1;
			liczKol = 0;
		}

		glVertex3f(cos(angle / 180.0f*3.14) + wspSr[1][X], sin(angle / 180.0f*3.14) + wspSr[1][Y], 0.0f);
		glVertex3f(cos(angle / 180.0f*3.14) + wspSr[1][X], sin(angle / 180.0f*3.14) + wspSr[1][Y], -grubosc);
		liczKol++;
		angle += kat;
	}

	wsp = wspPkt[1][X] - skokUksos;
	while (wsp >= wspPkt[2][X])
	{
		if (color == 1 && liczKol == 16)
		{
			glColor3f(1, 0, 0);
			color = 0;
			liczKol = 0;
		}
		if (color == 0 && liczKol == 16)
		{
			glColor3f(0, 1, 0);
			color = 1;
			liczKol = 0;
		}
		glVertex3f(wsp, a[0] * wsp + b[0], 0);
		glVertex3f(wsp, a[0] * wsp + b[0], -grubosc);
		wsp -= skokUksos;
		liczKol++;
	}
	angle = 65;
	while (angle <= 120)
	{
		if (color == 1 && liczKol == 16)
		{
			glColor3f(1, 0, 0);
			color = 0;
			liczKol = 0;
		}
		if (color == 0 && liczKol == 16)
		{
			glColor3f(0, 1, 0);
			color = 1;
			liczKol = 0;
		}
		glVertex3f(cos(angle / 180.0f*3.14) + wspSr[2][X], sin(angle / 180.0f*3.14) + wspSr[2][Y], 0.0f);
		glVertex3f(cos(angle / 180.0f*3.14) + wspSr[2][X], sin(angle / 180.0f*3.14) + wspSr[2][Y], -grubosc);
		liczKol++;
		angle += kat;
	}

	wsp = wspPkt[3][X] - skokUksos;
	while (wsp >= wspPkt[0][X])
	{
		if (color == 1 && liczKol == 16)
		{
			glColor3f(1, 0, 0);
			color = 0;
			liczKol = 0;
		}
		if (color == 0 && liczKol == 16)
		{
			glColor3f(0, 1, 0);
			color = 1;
			liczKol = 0;
		}
		glVertex3f(wsp, a[1] * wsp + b[1], 0);
		glVertex3f(wsp, a[1] * wsp + b[1], -grubosc);
		wsp -= skokUksos;
		liczKol++;
	}
	angle = 125;
	while (angle <= 270)
	{
		if (color == 1 && liczKol == 16)
		{
			glColor3f(1, 0, 0);
			color = 0;
			liczKol = 0;
		}
		if (color == 0 && liczKol == 16)
		{
			glColor3f(0, 1, 0);
			color = 1;
			liczKol = 0;
		}

		glVertex3f(cos(angle / 180.0f*3.14) + wspSr[0][X], sin(angle / 180.0f*3.14) + wspSr[0][Y], 0.0f);
		glVertex3f(cos(angle / 180.0f*3.14) + wspSr[0][X], sin(angle / 180.0f*3.14) + wspSr[0][Y], -grubosc);
		liczKol++;
		angle += kat;
	}
	glEnd();

	//TYL:
	glColor3d(0.9, 0.3, 0);

	glBegin(GL_QUADS);
	glVertex3f(wspSr[0][X], wspSr[0][Y], -grubosc);
	glVertex3f(wspSr[1][X], wspSr[1][Y], -grubosc);
	glVertex3f(wspSr[1][X], 0.0f, -grubosc);
	glVertex3f(wspSr[0][X], 0.0f, -grubosc);

	glVertex3f(wspSr[2][X], wspSr[2][Y], -grubosc);
	glVertex3f(wspPkt[2][X], wspPkt[2][Y], -grubosc);
	glVertex3f(wspPkt[1][X], wspPkt[1][Y], -grubosc);
	glVertex3f(wspSr[1][X], wspSr[1][Y], -grubosc);

	glVertex3f(wspSr[2][X], wspSr[2][Y], -grubosc);
	glVertex3f(wspSr[0][X], wspSr[0][Y], -grubosc);
	glVertex3f(wspPkt[0][X], wspPkt[0][Y], -grubosc);
	glVertex3f(wspPkt[3][X], wspPkt[3][Y], -grubosc);

	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(wspSr[2][X], wspSr[2][Y], -grubosc);
	glVertex3f(wspSr[1][X], wspSr[1][Y], -grubosc);
	glVertex3f(wspSr[0][X], wspSr[0][Y], -grubosc);
	glEnd();


	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(wspSr[1][X], wspSr[1][Y], -grubosc);
	angle = 60;
	while (angle >= -90)
	{
		glVertex3f(cos(angle / 180.0f*3.14) + wspSr[1][X], sin(angle / 180.0f*3.14) + wspSr[1][Y], -grubosc);
		angle -= kat;
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(wspSr[2][X], wspSr[2][X], -grubosc);
	angle = 120;
	while (angle >= 60)
	{
		glVertex3f(cos(angle / 180.0f*3.14) + wspSr[2][X], sin(angle / 180.0f*3.14) + wspSr[2][Y], -grubosc);
		angle -= kat;
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(wspSr[0][X], wspSr[0][Y], -grubosc);
	angle = 270;
	while (angle >= 120)
	{
		glVertex3f(cos(angle / 180.0f*3.14) + wspSr[0][X], sin(angle / 180.0f*3.14) + wspSr[0][Y], -grubosc);
		angle -= kat;
	}
	glEnd();
}
void Robot::ramie(double r1, double r2, double h, double d)
{
	//prawa strona
	double angle, x, y;
	glBegin(GL_TRIANGLE_FAN);
	glColor3d(1, 0, 0);
	glVertex3d(d, 0.0f, 0.0f);
	for (angle = 0.0f; angle <= (M_PI); angle += (M_PI / 8.0f))
	{
		x = r2*sin(angle);
		y = r2*cos(angle);
		glVertex3d(x + d, y, 0.0);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (angle = 0.0f; angle <= (M_PI); angle += (M_PI / 8.0f))
	{
		x = r2*sin(angle);
		y = r2*cos(angle);
		glVertex3d(x + d, y, 0);
		glVertex3d(x + d, y, h);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(d, 0.0f, h);
	for (angle = -M_PI; angle >= -(2.0f*M_PI); angle -= (M_PI / 8.0f))
	{
		x = r2*sin(angle);
		y = r2*cos(angle);
		glVertex3d(x + d, y, h);
	}
	glEnd();

	//lewa strona

	glColor3d(0, 1, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0.0f, 0.0f, 0.0f);
	for (angle = M_PI; angle <= (2 * M_PI); angle += (M_PI / 8.0f))
	{
		x = r1*sin(angle);
		y = r1*cos(angle);
		glVertex3d(x, y, 0.0);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (angle = M_PI; angle <= (2 * M_PI); angle += (M_PI / 8.0f))
	{
		x = r1*sin(angle);
		y = r1*cos(angle);
		glVertex3d(x, y, 0);
		glVertex3d(x, y, h);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0.0f, 0.0f, h);
	for (angle = 0.0f; angle >= -(M_PI); angle -= (M_PI / 8.0f))
	{
		x = r1*sin(angle);
		y = r1*cos(angle);
		glVertex3d(x, y, h);
	}
	glEnd();

	glBegin(GL_QUADS);
	glColor3d(0, 0, 1);
	glVertex3d(0, r1, 0);
	glVertex3d(0, r1, h);
	glVertex3d(d, r2, h);
	glVertex3d(d, r2, 0);

	glVertex3d(0, r1, h);
	glVertex3d(0, -r1, h);
	glVertex3d(d, -r2, h);
	glVertex3d(d, r2, h);

	glVertex3d(0, r1, 0);
	glVertex3d(d, r2, 0);
	glVertex3d(d, -r2, 0);
	glVertex3d(0, -r1, 0);

	glVertex3d(0, -r1, h);
	glVertex3d(0, -r1, 0);
	glVertex3d(d, -r2, 0);
	glVertex3d(d, -r2, h);

	glEnd();

}
void Robot::figura1(float a, float b, float c)
{
	glBegin(GL_QUADS);

	glNormal3d(0, 0, 1);
	glVertex3d(0, 0, 0);
	glVertex3d(a, 0, 0);
	glVertex3d(a - a / 8.0, b, 0);
	glVertex3d(a / 8.0, b, 0);

	glColor3d(0, 0.5, 1);
	glNormal3d(1, 0, 0);
	glVertex3d(a, 0, 0);
	glVertex3d(a, 0, -c);
	glVertex3d(a - a / 8.0, b, -c);
	glVertex3d(a - a / 8.0, b, 0);

	glColor3d(0.0, 1, 0.5);
	glNormal3d(0, 0, -1);
	glVertex3d(a, 0, -c);
	glVertex3d(0, 0, -c);
	glVertex3d(a / 8.0, b, -c);
	glVertex3d(a - a / 8.0, b, -c);

	glColor3d(0.0, 1, 1);
	glNormal3d(-1, 0, 0);
	glVertex3d(0, 0, -c);
	glVertex3d(0, 0, 0);
	glVertex3d(a / 8.0, b, 0);
	glVertex3d(a / 8.0, b, -c);

	glColor3d(1.0, 0, 1);
	glNormal3d(0, 1, 0);
	glVertex3d(a / 8.0, b, 0);
	glVertex3d(a - a / 8.0, b, 0);
	glVertex3d(a - a / 8.0, b, -c);
	glVertex3d(a / 8.0, b, -c);

	glColor3d(1.0, 1, 0);
	glNormal3d(0, -1, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, -c);
	glVertex3d(a, 0, -c);
	glVertex3d(a, 0, 0);
	glEnd();
}

void Robot::Draw(int obrotL, int obrotR)
{


	float rozstaw = 10;

	glPushMatrix();
	//glTranslatef(-7.5, 2, rozstaw / 2);
	figura1(10, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(8, 0, 0);
	gasienica(obrotR);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(8, 0, 10 +1.5);
	gasienica(obrotL);
	glPopMatrix();
}
void Robot::Draw()
{
	glPushMatrix();
	switch (OriPosition)
	{
	case oLeftWheel:
		Origin = lWheel;
		glTranslatef(LeftWheel.x, LeftWheel.y, LeftWheel.z);
		glRotatef(oldRot, 0, 1, 0);
		glRotatef(Rotation.y, 0, 1, 0);
		glTranslatef(-Origin.x, -Origin.y, -Origin.z);
		glTranslatef(Translation.x, Translation.y, Translation.z);
		tmp = Matrixf(LeftWheel)*Matrixf(oldRot)*Matrixf(Rotation.y)*Matrixf(-Origin.x, -Origin.y, -Origin.z)*Matrixf(Translation);
		break;
	case oRightWheel:
		Origin = rWheel;
		glTranslatef(RightWheel.x, RightWheel.y, RightWheel.z);
		glRotatef(oldRot, 0, 1, 0);
		glRotatef(Rotation.y, 0, 1, 0);
		glTranslatef(-Origin.x, -Origin.y, -Origin.z);
		glTranslatef(Translation.x, Translation.y, Translation.z);
		tmp = Matrixf(RightWheel)*Matrixf(oldRot)*Matrixf(Rotation.y)*Matrixf(-Origin.x, -Origin.y, -Origin.z)*Matrixf(Translation);
		break;
	case oCenter:
		Origin = center;
		glTranslatef(Center.x, Center.y, Center.z);
		glRotatef(oldRot, 0, 1, 0);
		glRotatef(Rotation.y, 0, 1, 0);
		glTranslatef(-Origin.x, -Origin.y, -Origin.z);
		glTranslatef(Translation.x, Translation.y, Translation.z);
		tmp = Matrixf(Center)*Matrixf(oldRot)*Matrixf(Rotation.y)*Matrixf(-Origin.x, -Origin.y, -Origin.z)*Matrixf(Translation);
		break;
	}
	LeftWheel = tmp *lWheel;
	RightWheel = tmp*rWheel;
	Center = tmp*center;
	oldRot += Rotation.y;

	Translation.x = 0;
	Translation.y = 0;
	Translation.z = 0;
	Rotation.y = 0;
	 Draw(0, 0);
	 glTranslatef(3, 10, -5);
	 Sensor1.Draw();
	 glPopMatrix();
}
void Robot::head(int obrot)
{
	glPushMatrix();
	glTranslatef(0.0003, 16.5224, -1.3122);
	glRotatef(obrot, 1, 0, 0);
	model[HEAD1].draw();
	glColor3ub(164, 164, 164);
	model[HEAD2].draw();
	glColor3ub(25, 25, 25);
	model[HEAD3].draw();
	//W³¹czenie ³¹czenia kolorów :
	glEnable(GL_BLEND);
	//Ustawienie bufora g³êbokoœci w tryb odczytu :
	glDepthMask(GL_FALSE);
	//Skonfigurowanie sposobu ³¹czenia kolorów :
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Okreœlenie koloru obiektu przezroczystego :
	glColor4ub(44, 54, 41, 180);
	model[HEAD4].draw();
	//Przywrócenie bufora g³êbokoœci w pe³ny tryb zapisu / odczytu:
	glDepthMask(GL_TRUE);
	//Wy³¹czenie ³¹czenia kolorów :
	glDisable(GL_BLEND);
	glPopMatrix();
}
void Robot::lArm(int lr, int ud)
{
	glPushMatrix();

	glColor3ub(92, 92, 92);
	glTranslatef(5.7539, 14.0014, -0.6319);
	glRotatef(ud, 1, 0, 0);
	model[L_ARM_PIVOT].draw();

	glColor3ub(209, 171, 20);
	glTranslatef(2.8714, 0, 0);
	glRotatef(lr, 0, 1, 0);
	model[L_ARM].draw();
	glColor3ub(164, 164, 164);
	model[L_HAND].draw();

	glPopMatrix();
}
void Robot::rArm(int lr, int ud)
{
	glPushMatrix();

	glColor3ub(92, 92, 92);
	glTranslatef(-5.7539, 14.0014, -0.6319);
	glRotatef(ud, 1, 0, 0);
	model[R_ARM_PIVOT].draw();

	glColor3ub(209, 171, 20);
	glTranslatef(-2.8714, 0, 0);
	glRotatef(lr, 0, 1, 0);
	model[R_ARM].draw();
	glColor3ub(164, 164, 164);
	model[R_HAND].draw();

	glPopMatrix();
}
void Robot::naped(float vl, float vr)
{
	glPushMatrix();

	glTranslatef(0.7222, 5.0414, -0.4206);

	glColor3ub(106, 87, 79);
	model[NAPED_MOCOWANIE_1].draw();

	glColor3ub(134, 44, 17);
	model[NAPED_MOCOWANIE_2].draw();

	glColor3ub(80, 80, 80);
	model[GASIENICA].draw();
	//L
	glColor3ub(106, 87, 79);
	glPushMatrix();
	glTranslatef(9.3861, -1.6844, -4.5619);
	glRotatef(vl, 1, 0, 0);
	model[LARGE_WHEEL].draw();
	glPopMatrix();
	//R
	glPushMatrix();
	glPushMatrix();
	glTranslatef(-10.8307, -1.6851, -4.5609);
	glRotatef(vr, 1, 0, 0);
	model[LARGE_WHEEL].draw();
	glPopMatrix();
	//L
	glPushMatrix();
	glPushMatrix();
	glTranslatef(9.3866, -2.4126, 4.241);
	glRotatef(vl*1.2, 1, 0, 0);
	model[MEDIUM_WHEEL].draw();
	glPopMatrix();
	//R
	glPushMatrix();
	glPushMatrix();
	glTranslatef(-10.831, -2.413, 4.2445);
	glRotatef(vr*1.2, 1, 0, 0);
	model[MEDIUM_WHEEL].draw();
	glPopMatrix();
	//L
	glPushMatrix();
	glPushMatrix();
	glTranslatef(9.3904, 0.8282, 2.1358);
	glRotatef(vl*1.5, 1, 0, 0);
	model[SMALL_WHEEL].draw();
	glPopMatrix();
	//R
	glPushMatrix();
	glPushMatrix();
	glTranslatef(-10.8308, 0.8281, 2.1373);
	glRotatef(vr*1.5, 1, 0, 0);
	model[SMALL_WHEEL].draw();
	glPopMatrix();
	//L
	glPushMatrix();
	glPushMatrix();
	glTranslatef(9.3864, 4.6568, -1.7999);
	glRotatef(vl*1.5, 1, 0, 0);
	model[SMALL_WHEEL].draw();
	glPopMatrix();
	//R
	glPushMatrix();
	glPushMatrix();
	glTranslatef(-10.8308, 4.6567, -1.7983);
	glRotatef(vr*1.5, 1, 0, 0);
	model[SMALL_WHEEL].draw();
	glPopMatrix();

	glPopMatrix(); 
}
void Robot::Rysuj(float vl, float vr, int heado, int llr, int lud, int rlr, int rud)
{
	//BODY
	glColor3ub(209, 171, 20);
	model[BODY].draw();

	//HEAD
	head(heado);

	//LEFT ARM
	lArm(llr, lud);

	//RIGHT ARM
	rArm(rlr,rud);

	//NAPED
	naped(vl,vr);

}