#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>


class objetos
{
private:
	float anguloCInferior;
	float anguloCCentral;
	float anguloCSuperior;
	float anguloRuedas;
	float xPatineta;
	float yPatineta;
	bool  vista;

public:
	void setAnguloCInferior(float a);
	float getAnguloCInferior();
	void setAnguloCCentral(float a);
	float getAnguloCCentral();
	void setAnguloCSuperior(float a);
	float getAnguloCSuperior();
	void setXPatineta(float a);
	float getXPatineta();
	void setAnguloRuedas(float a);
	float getAnguloRuedas();
	void setVista(bool a);
	bool getVista();
	objetos(void);
	objetos(float i, float c, float s, float x, float y, float r,bool v);
	void dibujar();
	void circulo(float r, float x, float y, int n);
	void relleno(float r, float x, float y, int n);
	void piso();
	void rectangulo(float a, float l, float x_center, float y_center);
	void triangulo();
	void dibujarCirculoInferior();
	void dibujarCirculoCentral();
	void dibujarCirculoSuperior();
	void dibujarLampara();
	void dibujarPatineta();
	void ejesCoordenada(float limite);
};

