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
	disparado = false;
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

void bloque::setDisparado(bool m)
{
	disparado = m;
}

bool bloque::getDisparado()
{
	return disparado;
}

void bloque::setExiste(bool e)
{
	existe = e;
}
bool bloque::getExiste(){
	return existe;
}

float bloque::getLargo()
{
	return largo;
}
float bloque::getAlto()
{
	return alto;
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

	float b_izq = b.getX() - b.getLargo()/2;
	float b_der = b.getX() + b.getLargo()/2;
	float b_arr = b.getY() + b.getAlto()/2;
	float b_abj = b.getY() - b.getAlto()/2;	

	return der >= b_izq && izq <= b_der && arr >= b_abj && abj <= b_arr && existe && b.getExiste();
}


bool bloque::colisionConNave(nave n)
{
	//lados del bloque
	float izq = x - largo/2;
	float der = x + largo/2;
	float arr = y + alto/2;
	float abj = y - alto/2;

	float n_arr = n.getY() + n.getAltura()/2;
	float n_abj = n.getY() - n.getAltura()/2;
	float n_izq = n.getX() - n.getBase()/2;
	float n_der = n.getX() + n.getBase()/2;

	return arr>=n_abj && izq<=n_der && der>=n_izq && abj<=n_arr && existe && n.getExiste();
}
