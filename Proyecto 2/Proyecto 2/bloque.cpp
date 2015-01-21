#include "bloque.h"

bloque::bloque(void)
{
	objeto();
}

bloque::bloque(float coord_x, float coord_y)
{
	x = coord_x;
	y = coord_y;
	alto = 1.0;
	largo = 1.0;
}

// constructor
bloque::bloque(float coord_x, float coord_y, float a, float l)
{
	x = coord_x;
	y = coord_y;
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
<<<<<<< HEAD
		glVertex2f(x + largo/2,y + alto/2);		
		glVertex2f(x + largo/2,y - alto/2);	
		glVertex2f(x - largo/2,y - alto/2);	
		glVertex2f(x - largo/2,y + alto/2);	
=======
		glVertex2f(largo/2,alto/2);		
		glVertex2f(largo/2,alto/2);	
		glVertex2f(largo/2,alto/2);	
		glVertex2f(largo/2,alto/2);	
>>>>>>> 5eec6926aa76af0f2ccb928e004a5f1db540f91b
	glEnd();
}