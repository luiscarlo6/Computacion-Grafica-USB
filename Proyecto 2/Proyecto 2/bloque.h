#pragma once
#include "objeto.h"

class bloque :
	public objeto
{
protected:
	float alto;
	float largo;
public:
	void setXY(float xNew, float yNew);
	float getX();
	float getY();

	bloque(void);
	bloque(float a, float l);

	virtual void dibujar(float x, float y);
	void incrementar(float *val);
};

