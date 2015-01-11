#include "objetos.h"

objetos::objetos(){
	anguloCInferior = 0;
	anguloCCentral = 0;
	anguloCSuperior = 0;	
	anguloRuedas = 0;
	xPatineta = 0;
	yPatineta = 0;
	
}

objetos::objetos(float i, float c, float s, float x, float y, float r){
	anguloCInferior = i;
	anguloCCentral = c;
	anguloCSuperior = s;
	anguloRuedas = r;
	xPatineta = x;
	yPatineta = y;
	
}
void objetos::setAnguloCInferior(float a){
	anguloCInferior = a;
}
float objetos::getAnguloCInferior(){
	return anguloCInferior;
}

void objetos::setAnguloCCentral(float a){
	anguloCCentral = a;
}
float objetos::getAnguloCCentral(){
	return anguloCCentral;
}

void objetos::setAnguloCSuperior(float a){
	anguloCSuperior = a;
}
float objetos::getAnguloCSuperior(){
	return anguloCSuperior;
}

void objetos::setXPatineta(float a){
	xPatineta = a;
}
float objetos::getXPatineta(){
	return xPatineta;
}

void objetos::setAnguloRuedas(float a){
	anguloRuedas = a;
}
float objetos::getAnguloRuedas(){
	return anguloRuedas;
}

void objetos::dibujar(){
	glLineWidth(2.5f);
	piso();
	dibujarLampara();
	dibujarPatineta();
}

void objetos::dibujarPatineta(){
	float pi = 3.14159265358979323846;
	glLineWidth(3.0f);
	glPushMatrix();		
		glTranslatef(xPatineta,yPatineta,0.0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(-0.5f,0.2f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(3.0f,0.0f,0.0f);
		glVertex3f(3.5f,0.2f,0.0f);
		glEnd();
		glPushMatrix();
			glTranslatef(0.5,-0.5,0.0);
			glRotatef(anguloRuedas,0.0,0.0,1.0);
			circulo(0.5,0.0,0.0,10);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(2.5,-0.5,0.0);
			glRotatef(anguloRuedas,0.0,0.0,1.0);
			circulo(0.5,0.0,0.0,10);
		glPopMatrix();

	glPopMatrix();
}

void objetos::dibujarLampara(){
	glColor3f(0.0f,1.0f,0.0f);
	dibujarCirculoInferior();
}

void objetos::dibujarCirculoInferior(){
	glPushMatrix();
		glTranslatef(-7.0,-7.5,0.0);
		glRotatef(anguloCInferior,0.0,0.0,1.0);
		circulo(0.5,0.0,0.0,18);
		rectangulo(4.0,0.5,0,2.0);
		dibujarCirculoCentral();
	glPopMatrix();

}

void objetos::dibujarCirculoCentral(){
	glPushMatrix();	
		glTranslatef(0.0f,4.0,0.0);
		glRotatef(anguloCCentral,0.0,0.0,1.0);
		circulo(0.5,0.0,0.0,50);
		rectangulo(5.0,0.5,0.0,2.5);
		dibujarCirculoSuperior();
	glPopMatrix();
}

void objetos::dibujarCirculoSuperior(){
	glPushMatrix();	
		glTranslatef(0.0f,5.0,0.0);
		glRotatef(anguloCSuperior,0.0,0.0,1.0);
		circulo(0.5,0.0,0.0,50);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.0f,2.0f,0.0f);
		glVertex3f(-1.0f,2.0f,0.0f);
		glEnd();
	glPopMatrix();
}
void objetos::piso(){
	glBegin(GL_LINES);
		glVertex3f(-10.0f,-9.0f,0.0f);
		glVertex3f(10.0f,-9.0f,0.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex3f(-9.0f,-9.0f,0.0f);
		glVertex3f(-9.0f,-8.0f,0.0f);
		glVertex3f(-5.0f,-8.0f,0.0f);
		glVertex3f(-5.0f,-9.0f,0.0f);
	glEnd();
}

void objetos::rectangulo(float alto, float largo, float x_center, float y_center){
	glBegin(GL_LINE_LOOP);
		glVertex3f((GLfloat) largo/2+x_center,(GLfloat) -alto/2+y_center,0.0f);
		glVertex3f((GLfloat) largo/2+x_center,(GLfloat) alto/2+y_center,0.0f);
		glVertex3f((GLfloat) -largo/2+x_center,(GLfloat) alto/2+y_center,0.0f);
		glVertex3f((GLfloat) -largo/2+x_center,(GLfloat) -alto/2+y_center,0.0f);	
	glEnd();
}

void objetos::circulo(float r, float x_center, float y_center, int n){
	float pi = 3.14159265358979323846;
	GLfloat x = 0;
	GLfloat y = 0;
	float angle = 0;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
	{
		x = (GLfloat) r * cos(angle) + x_center;
		y = (GLfloat) r * sin(angle) + y_center;
		//glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(x,y,0.0f);
		angle += 2*pi/n;
	}
	glEnd();
}
