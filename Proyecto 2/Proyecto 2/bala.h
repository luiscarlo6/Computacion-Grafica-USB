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
		float getRadio();

		void dibujar();

		bool colisionConBala(bala b);
		bool colisionConBloque(bloque b);
		bool colisionConNave(nave n);
};

