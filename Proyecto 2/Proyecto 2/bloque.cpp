#include "bloque.h"

bloque::bloque(void)
{
	objeto();
}

// constructor
bloque::bloque(float a, float l)
{
	alto = a;
	largo = l;
}

void bloque::setXY(float xNew, float yNew){
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

float bloque::getX(){
	return x;
}

float bloque::getY(){
	return y;
}

void bloque::dibujar(float a, float b)
{	
	glPushMatrix();
	glTranslatef(x,y,0.0);
		glBegin(GL_POLYGON);
			glVertex2f(-largo/2,alto/2); 
			glVertex2f(largo/2,alto/2); 
			glVertex2f(largo/2,-alto/2); 
			glVertex2f(-largo/2,-alto/2); 
		glEnd();
	glPopMatrix();
}


