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
	x = xNew;
	y = yNew;
}

float bloque::getX(){
	return x;
}

float bloque::getY(){
	return y;
}

void bloque::dibujar()
{	
	glBegin(GL_POLYGON);
		glVertex2f(-largo/2,alto/2); 
		glVertex2f(largo/2,alto/2); 
		glVertex2f(largo/2,-alto/2); 
		glVertex2f(-largo/2,-alto/2); 
	glEnd();
}