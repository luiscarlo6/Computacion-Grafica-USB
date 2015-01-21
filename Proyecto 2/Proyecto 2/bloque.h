#pragma once
#include "objeto.h"

class bloque :
	public objeto
{
protected:
	float alto;
	float largo;
	bool esMorado;
	bool existe;
public:
	void setXY(float xNew, float yNew);
	void setMorado(bool m);
	bool getMorado();
	float getX();
	float getY();

	bloque(void);
	bloque(float a, float l);

	virtual void dibujar();
};

