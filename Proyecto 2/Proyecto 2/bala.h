#pragma once
#include "objeto.h"

class bala :
	public objeto
{

protected:
	float radio;
public:
	bala(void);
	bala(float coord_x, float coord_y);
	bala(float coord_x, float coord_y, float r);

	virtual void dibujar();
};

