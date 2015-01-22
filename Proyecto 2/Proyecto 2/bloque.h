#pragma once
#include "objeto.h"
#include "nave.h"

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

		bool colisionConNave(nave n);
		bool colisionConCuadrado(bloque b);
		void dibujar();
};

