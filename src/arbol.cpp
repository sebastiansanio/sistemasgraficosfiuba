#include "arbol.h"


arbol::arbol(float altura,float radio,float posX,float posY){
	this->altura=altura;
	this->radio=radio;
	this->posX=posX;
	this->posY=posY;
	hoja::inicializar();
	tronco = new rama(altura,radio,0,0,0);
	edad=1;
}

void arbol::envejecer(){

	edad+=1;
	tronco->agregarRama();
}

void arbol::rejuvenecer(){
	if(edad>1){
		edad-=1;
		tronco->quitarRama();
	}
}

void arbol::dibujar(){
	glPushMatrix();
	glTranslatef(posX,posY,0.0);
	glScalef(1.0+0.25*(edad-1),1.0+0.25*(edad-1),1.0+0.25*(edad-1));
	tronco->dibujar();
	tronco->dibujarHijos();
	glPopMatrix();

}
