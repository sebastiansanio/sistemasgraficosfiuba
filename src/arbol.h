#ifndef ARBOL_H_
#define ARBOL_H_

#include <GL/glut.h>
#include "rama.h"
#include "hoja.h"

class arbol{

	private:
		float altura;
		float radio;
		int edad;
		rama* tronco;
		float posX;
		float posY;

	public:
		arbol(float altura,float radio,float posX,float posY);
		void dibujar();
		void envejecer();
		void rejuvenecer();


};

#endif
