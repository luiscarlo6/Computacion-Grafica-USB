#include "bala.h"


bala::bala(void)
{
	objeto();
}

bala::bala(float r)
{
	radio = r;
}

void bala::setXY(float xNew, float yNew){
	if (xNew>=50)
		x=50;
	else if (xNew<=-50)
		x=-50;
	else
		x = xNew;
	
	if (yNew>=50){
		y=50;
		existe=false;
	}
	else if (yNew<=-50){
		y=-50;
		existe=false;
	}
	else
		y = yNew;
}

float bala::getX(){
	return x;
}

float bala::getY(){
	return y;
}

float bala:: getRadio(){
	return radio;
}

void bala::dibujar()
{
	float pi = 3.14159265358979323846;
	GLfloat xBorde = 0;
	GLfloat yBorde = 0;
	float angle = 0;
	int n = 20;

	if(existe){
		glPushMatrix();
			glTranslatef(x,y,0.0);
			glBegin(GL_POLYGON);
				for (int i = 0; i < n; i++)
				{
					xBorde = (GLfloat) radio * cos(angle);
					yBorde = (GLfloat) radio * sin(angle);
					glVertex2f(xBorde,yBorde);
					angle += 2*pi/n;
				}
			glEnd();
		glPopMatrix();
	}

}

bool bala::colisionConBloque(bloque b)
{
	float izq = x - radio;
	float der = x + radio;
	float arr = y + radio;
	float abj = y - radio;

	float b_izq = b.getX() - b.getLargo()/2;
	float b_der = b.getX() + b.getLargo()/2;
	float b_arr = b.getY() + b.getAlto()/2;
	float b_abj = b.getY() - b.getAlto()/2;	

	return (arr>=b_abj && izq<=b_der && der>=b_izq && abj<=b_arr && existe && b.getExiste());
}

bool bala::colisionConNave(nave n)
{
	//lados del bloque
	float izq = x - radio;
	float der = x + radio;
	float arr = y + radio;
	float abj = y - radio;

	float n_arr = n.getY() + n.getAltura()/2;
	float n_abj = n.getY() - n.getAltura()/2;
	float n_izq = n.getX() - n.getBase()/2;
	float n_der = n.getX() + n.getBase()/2;

	return arr>=n_abj && izq<=n_der && der>=n_izq && abj<=n_arr && existe && n.getExiste();
}

bool bala::colisionConBala(bala b)
{
	float distance = sqrt(pow(abs(b.getX()- x),2) + pow(abs(b.getY() - y),2));
	
	return ((radio + b.getRadio()) > distance) && existe && b.getExiste();
}