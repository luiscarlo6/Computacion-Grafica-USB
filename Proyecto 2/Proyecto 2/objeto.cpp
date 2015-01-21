#include "objeto.h"

objeto::objeto(void)
{
	x = 0.0;
	y = 0.0;
}

// constructor
objeto::objeto(float coord_x, float coord_y)
{
	x = coord_x;
	y = coord_y;

}

void objeto::dibujar()
{
	glPointSize(4.0f);
	glBegin(GL_POINTS);
		glVertex2f(x, y);
	glEnd();
}