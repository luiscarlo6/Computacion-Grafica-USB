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

void bloque::dibujar()
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