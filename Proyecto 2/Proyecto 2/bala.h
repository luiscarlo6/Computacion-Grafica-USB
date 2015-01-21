#pragma once
#include "objeto.h"

class bala :
	public objeto
{

protected:
	float radio;
public:
	bala(void);
	bala(float r);

	virtual void dibujar();
};

