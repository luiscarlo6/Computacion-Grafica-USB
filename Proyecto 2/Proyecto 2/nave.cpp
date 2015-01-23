#include "nave.h"

nave::nave(void)
{
	objeto();
}

//constructor
nave::nave(float b, float a)
{
	base = b;
	altura = a;
}

void nave::setXY(float cx, float cy){
	if (cx>=(49-(base/2)))
		x=49-(base/2);
	else if (cx<=(-49+(base/2)))
		x=-49+(base/2);
	else
		x = cx;
	
	if (cy>=50)
		y=50;
	else if (cy<=-50)
		y=-50;
	else
		y = cy;
}

void nave::setEnemigoXY(float cx, float cy){
	x = cx;
	y = cy;
}

float nave::getX(){
	return x;
}

float nave::getY(){
	return y;
}

float nave::getBase()
{
	return base;
}

float nave::getAltura()
{
	return altura;
}

void nave::dibujar()
{
	if (existe){
		glPushMatrix();
			glTranslatef(x,y,0.0);
			glBegin(GL_TRIANGLES);
				glVertex2f(0.0, altura/2);
				glVertex2f(base/2, -altura/2);
				glVertex2f(-base/2, -altura/2);
			glEnd();
		glPopMatrix();
	}
}
