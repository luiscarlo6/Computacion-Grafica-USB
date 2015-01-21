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
	bloque(float coord_x, float coord_y);
	bloque(float coord_x, float coord_y, float a, float l);

	virtual void dibujar();
};

