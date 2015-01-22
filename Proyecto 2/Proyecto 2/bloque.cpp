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
	esMorado = false;
	existe = true;
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

void bloque::setMorado(bool m)
{
	esMorado = m;
}

bool bloque::getMorado()
{
	return esMorado;
}

void bloque::setExiste(bool e)
{
	existe = e;
}
bool bloque::getExiste(){
	return existe;
}

void bloque::dibujar()
{	
	if (existe){
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
}

bool bloque::colisionConCuadrado(bloque b)
{
	//lados del bloque
	float izq = x - largo/2;
	float der = x + largo/2;
	float arr = y + alto/2;
	float abj = y - alto/2;

	float b_izq = b.getX() - largo/2;
	float b_der = b.getX() + largo/2;
	float b_arr = b.getY() + alto/2;
	float b_abj = b.getY() - alto/2;	

	return der >= b_izq && izq <= b_der && arr >= b_abj && abj <= b_arr ;
}

