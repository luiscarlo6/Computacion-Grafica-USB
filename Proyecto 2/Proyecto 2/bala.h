#pragma once
#include "objeto.h"
#include "bloque.h"

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

		void dibujar();
		bool colisionConBloque(bloque b);
		bool colisionConNave(nave n);
};

