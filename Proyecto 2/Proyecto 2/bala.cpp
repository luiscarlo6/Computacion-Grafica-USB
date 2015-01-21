#include "bala.h"


bala::bala(void)
{
	objeto();
}

bala::bala(float coord_x, float coord_y)
{
	x = coord_x;
	y = coord_y;
	radio = 1.0;
}
bala::bala(float coord_x, float coord_y, float r)
{
	x = coord_x;
	y = coord_y;
	radio = r;
}

void bala::dibujar()
{
	float pi = 3.14159265358979323846;
	GLfloat xBorde = 0;
	GLfloat yBorde = 0;
	float angle = 0;
	int n = 20;

	glBegin(GL_LINE_LOOP);
		for (int i = 0; i < n; i++)
		{
			xBorde = (GLfloat) radio * cos(angle) + this->x;
			yBorde = (GLfloat) radio * sin(angle) + this->y;
			//glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(xBorde,yBorde,0.0f);
			angle += 2*pi/n;
		}
	glEnd();
}
