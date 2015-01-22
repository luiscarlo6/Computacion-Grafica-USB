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
		float getX();
		float getY();

		nave(void);
		nave(float b, float a);

		virtual void dibujar();
};

