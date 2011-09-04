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
}

void arbol::envejecer(){

	if(crece){
		edad+=1;
		if(edad % 75 == 0){
			tronco->agregarRama();

		}
	}


}

void arbol::crecimiento(){
	crece=!crece;
}



void arbol::rejuvenecer(){
	if(edad>1){
		if(edad % 75 == 0){
			tronco->quitarRama();
		}
		edad-=1;


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
