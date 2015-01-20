#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

class objeto
{
protected:
	float x;
	float y;

public:
	objeto(void);
	objeto(float coord_x, float coord_y);

	virtual void dibujar();
};

