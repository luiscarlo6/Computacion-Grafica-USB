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
	if (cx>=50)
		x=50;
	else if (cx<=-50)
		x=-50;
	else
		x = cx;
	
	if (cy>=50)
		y=50;
	else if (cy<=-50)
		y=-50;
	else
		y = cy;
}

float nave::getX(){
	return x;
}

float nave::getY(){
	return y;
}

void nave::dibujar()
{
	if (existe){
		glPushMatrix();
			glTranslatef(x,y,0.0);
			glBegin(GL_TRIANGLES);
				  glVertex2f(base-base, 0.0f); // V0
				  glVertex2f(base/2, altura); // V1
				  glVertex2f(base, 0.0f); // V2
			glEnd();
		glPopMatrix();
	}
}
