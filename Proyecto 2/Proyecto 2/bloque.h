#pragma once
#include "objeto.h"

class bloque :
	public objeto
{
protected:
	float alto;
	float largo;
public:

	bloque(void);
	bloque(float a, float l);

	virtual void dibujar();
};

