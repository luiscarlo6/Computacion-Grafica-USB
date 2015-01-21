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

bloque::bloque(float coord_x, float coord_y, float a, float l)
{
	x = coord_x;
	y = coord_y;
	alto = a;
	largo = l;
}
void bloque::dibujar()
{	
	glBegin(GL_POLYGON);
		glVertex2f(x + largo/2,y + alto/2);		
		glVertex2f(x + largo/2,y - alto/2);	
		glVertex2f(x - largo/2,y - alto/2);	
		glVertex2f(x - largo/2,y + alto/2);	
	glEnd();
}