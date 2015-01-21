#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

class objeto
{
protected:
	float x;
	float y;
	bool existe;
public:
	//setters,getter
	void setXY(float x, float y);
	float getX();
	float getY();
	void setExiste(bool e);
	bool getExiste();

	objeto(void);
	objeto(float coord_x, float coord_y);

	virtual void dibujar();
};

