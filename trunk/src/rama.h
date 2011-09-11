#ifndef RAMA_H_
#define RAMA_H_
#include <GL/glut.h>
#include "aleatorio.h"
#include <stdio.h>
#include <stdlib.h>
#include "hoja.h"
class rama{

	private:
		const static int precision=20;

		float tall;
		float radio;
		float radio2;
		float alturaPadre;
		float rotacion1;
		float rotacion2;
		int cantHijos;
		int edad;
		rama** subRamas;

		GLuint dlTapa;
		GLuint dlBorde;


		void tapa();
		void borde();

	public:
		rama(float alto, float radio,float alturaPadre,float rotacion1,float rotacion2);
		~rama();
		void dibujar();
		void dibujarHijos();
		void agregarRama();
		void quitarRama();
		int getCantHijos();
		float getAlturaPadre();
		float getRotacion1();
		float getRotacion2();
		void crecer();
};

#endif
