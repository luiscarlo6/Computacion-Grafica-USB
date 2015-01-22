#pragma once
#include "objeto.h"

class nave:
	public objeto
{
	//atributos
	protected:
		float base;
		float altura;

	//metodos
	public:
		void setXY(float cx, float cy);
		void setEnemigoXY(float cx, float cy);
		float getX();
		float getY();
		float getAltura();
		float getBase();

		nave(void);
		nave(float b, float a);

		virtual void dibujar();
};

