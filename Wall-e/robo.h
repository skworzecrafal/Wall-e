#include <GL/glut.h>
#include <math.h>

#define M_PI 3.14
#define X 0
#define Y 1

GLUquadricObj *obj = gluNewQuadric();
void gasienica(int obrot)
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
	float ilosc = sqrtf(pow((wspPkt[2][Y] - wspPkt[1][Y]), 2) + pow((wspPkt[2][X] - wspPkt[1][X]), 2))/skok;
	float skokUksos = (wspPkt[1][X] - wspPkt[2][X])/ilosc;
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
	while( angle <= 60.0 )
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
	while ( angle <= 270.0 )
	{
		glVertex3f(cos(angle / 180.0f*3.14) + wspSr[0][X], sin(angle / 180.0f*3.14) + wspSr[0][Y], 0.0f);
		angle += kat;
	}
	glEnd();
	
	//TASMA:
	int liczKol = 16-obrot;
	int color = 1;
	glColor3f(1.0, 0, 0);
	float wsp = wspSr[0][X];
	glBegin(GL_QUAD_STRIP);
	while (wsp<=wspSr[1][X])
	{
		if (color==1 && liczKol==16)
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
	while (angle <= 60 )
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
		glVertex3f(wsp, a[0]*wsp + b[0], 0);
		glVertex3f(wsp, a[0]*wsp + b[0], -grubosc);
		wsp -= skokUksos;
		liczKol++;
	}
	angle = 65;
	while (angle <= 120 )
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
	while ( angle <= 270 )
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
	while (angle >= -90 )
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
	while ( angle >= 120 )
	{
		glVertex3f(cos(angle / 180.0f*3.14) + wspSr[0][X], sin(angle / 180.0f*3.14) + wspSr[0][Y], -grubosc);
		angle -= kat;
	}
	glEnd();
}

void ramie(double r1, double r2, double h, double d)
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
/*
		_________
	   /         \
	  /           \
	 /			   \
	 ---------------
*/
void figura1(float a, float b, float c)
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

void robot(int obrotL, int obrotR)
{
	float rozstaw = 6;

	glPushMatrix();
	glTranslatef(-7.5, 2, rozstaw / 2);
	figura1(15, 10, rozstaw);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -rozstaw / 2);
	gasienica(obrotR);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, rozstaw / 2 + 1.5);
	gasienica(obrotL);
	glPopMatrix();
}