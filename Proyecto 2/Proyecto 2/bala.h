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

		void setXY(float xNew, float yNew);
		float getX();
		float getY();

		virtual void dibujar();
};

