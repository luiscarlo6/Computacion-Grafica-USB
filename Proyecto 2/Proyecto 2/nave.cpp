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
	existe = true;
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

void nave::setExiste(bool e)
{
	existe = e;
}

bool nave::getExiste(){
	return existe;
}

void nave::dibujar()
{
	if (existe){
		glPushMatrix();
			glTranslatef(x,y,0.0);
			glBegin(GL_LINE_LOOP);
				glVertex2f(1.0,0.0); 
				glVertex2f(2.0,3.0); 
				glVertex2f(3.0,0.0);
			glEnd();
		glPopMatrix();
	}
}
