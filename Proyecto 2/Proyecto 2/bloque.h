#pragma once
#include "objeto.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

class bloque :
	public objeto
{
protected:
	float alto;
	float largo;
public:
	void setXY(float x, float y);
	float getX();
	float getY();

	bloque(void);
	bloque(float coord_x, float coord_y);
	bloque(float coord_x, float coord_y, float a, float l);

	virtual void dibujar();
};

