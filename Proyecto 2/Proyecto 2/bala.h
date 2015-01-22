#pragma once
#include "objeto.h"

class bala :
	public objeto
{
	//atributos
	protected:
		float radio;

	//metodos
	public:
		bala(void);
		bala(float r);

		virtual void dibujar();
};

