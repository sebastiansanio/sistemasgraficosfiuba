#include "arbol.h"


arbol::arbol(float altura,float radio,float posX,float posY){
	this->altura=altura;
	this->radio=radio;
	this->posX=posX;
	this->posY=posY;
	hoja::inicializar();
	tronco = new rama(altura,radio,0,0,0);
	edad=1;
	crece=true;
	ratioDeCrecimiento=1;
}

arbol::~arbol(){
	delete tronco;

}

void arbol::envejecer(){

	if(crece){
		for(int contador=0;contador<ratioDeCrecimiento;contador++){
			edad+=1;
			tronco->crecer();
			if(edad % 60 == 0){
				tronco->agregarRama();

			}
		}

	}


}

void arbol::crecimiento(){
	crece=!crece;
}

void arbol::aumentarCrecimiento(){
	ratioDeCrecimiento++;
}
void arbol::disminuirCrecimiento(){
	if(ratioDeCrecimiento>1){
		ratioDeCrecimiento--;
	}


}

void arbol::dibujar(){
	glPushMatrix();
	glTranslatef(posX,posY,0.0);
	glScalef(1.0+0.0125*(edad-1),1.0+0.0125*(edad-1),1.0+0.0125*(edad-1));
	tronco->dibujar();
	tronco->dibujarHijos();
	glPopMatrix();

}
