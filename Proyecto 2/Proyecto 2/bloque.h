#pragma once
#include "objeto.h"

class bloque :
	public objeto
{
	//atributos
	protected:
		float alto;
		float largo;
		bool esMorado;
		bool existe;
	// metodos
	public:
		void setXY(float xNew, float yNew);
		void setMorado(bool m);
		bool getMorado();
		float getX();
		float getY();
		void setExiste(bool e);
		bool getExiste();

		bloque(void);
		bloque(float a, float l);

		virtual void dibujar();
};

