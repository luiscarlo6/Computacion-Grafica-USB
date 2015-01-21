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

void objeto::setXY(float xNew, float yNew){
	if (xNew>=50)
		x=50;
	else if (xNew<=-50)
		x=-50;
	else
		x = xNew;
	
	if (yNew>=50)
		y=50;
	else if (yNew<=-50)
		y=-50;
	else
		y = yNew;
}

float objeto::getX(){
	return x;
}
float objeto::getY(){
	return y;
}

void objeto::dibujar()
{
	glPointSize(4.0f);
	glBegin(GL_POINTS);
		glVertex2f(0.0, 0.0);
	glEnd();
}