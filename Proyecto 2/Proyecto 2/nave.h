#pragma once
#include "objeto.h"

class nave:
	public objeto
{
	//atributos
	protected:
		float base;
		float altura;
		bool existe;

	//metodos
	public:
		void setXY(float cx, float cy);
		float getX();
		float getY();
		void setExiste(bool e);
		bool getExiste();

		nave(void);
		nave(float b, float a);

		virtual void dibujar();
};

