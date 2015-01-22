#include "bala.h"


bala::bala(void)
{
	objeto();
}

bala::bala(float r)
{
	radio = r;
}

void bala::dibujar()
{
	float pi = 3.14159265358979323846;
	GLfloat xBorde = 0;
	GLfloat yBorde = 0;
	float angle = 0;
	int n = 20;

	glBegin(GL_POLYGON);
		for (int i = 0; i < n; i++)
		{
			xBorde = (GLfloat) radio * cos(angle);
			yBorde = (GLfloat) radio * sin(angle);
			glVertex3f(xBorde,yBorde,0.0f);
			angle += 2*pi/n;
		}
	glEnd();
}
