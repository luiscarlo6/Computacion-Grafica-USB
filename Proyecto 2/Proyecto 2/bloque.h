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
		//sets y gets
		void setXY(float xNew, float yNew);
		void setMorado(bool m);
		bool getMorado();
		float getX();
		float getY();
		void setExiste(bool e);
		bool getExiste();
		float getLargo();
		float getAlto();
		//constructores
		bloque(void);
		bloque(float a, float l);

		bool colisionConCuadrado(bloque b);
		void dibujar();
};

