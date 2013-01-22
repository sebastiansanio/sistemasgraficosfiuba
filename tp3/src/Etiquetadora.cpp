/*
 * Etiquetadora.cpp
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#include "Etiquetadora.h"
#define ETIQUE_SUP 2.0
#define ETIQUE_INF 1.1
#define ETIQUE_VELOCIDAD 0.05

Etiquetadora::Etiquetadora() {
	this->cubeRef = new CubeRef(1.0,1.0,1.0);
	this->portaEtiqueta = new PortaEtiqueta();
	this->posEtiquetadora = ETIQUE_SUP;
	this->moviendo=false;
}

void Etiquetadora::print() {
	glPushMatrix();
		glPushMatrix();
			glTranslatef(0.0,0.0,1.8);
			glScalef(0.5,0.5,1.0);
			cubeRef->print();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0,0.0,0.4);
			glScalef(0.3,0.3,0.4);
			cubeRef->print();
		glPopMatrix();
		//En 1.1 está por arriba de la base de la botella, en 2.0 por arriba de la tapa
		glTranslatef(0.0,-1.0,posEtiquetadora);
		portaEtiqueta->print();
		glScalef(0.02,0.3,0.05);
		glTranslatef(12.5,0.6,12.0);
		cubeRef->print();
		glTranslatef(-25,0.0,0.0);
		cubeRef->print();
	glPopMatrix();
	mover();
}

void Etiquetadora::start() {
	if(!moviendo) {
		this->moviendo = true;
		this->subiendo = false;
		this->posEtiquetadora = ETIQUE_SUP - ETIQUE_VELOCIDAD;
	}
}

void Etiquetadora::mover() {
	if(this->moviendo) {
		if(this->posEtiquetadora >= ETIQUE_SUP) {
			this->subiendo = false;
			this->moviendo = false;
		} else if (this->posEtiquetadora <= ETIQUE_INF) {
			this->subiendo = true;
		}

		if(this->subiendo) {
			this->posEtiquetadora += ETIQUE_VELOCIDAD;
		} else {
			this->posEtiquetadora -= ETIQUE_VELOCIDAD;
		}
	}
}

Etiquetadora::~Etiquetadora() {
	// TODO Auto-generated destructor stub
}

