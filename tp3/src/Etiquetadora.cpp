/*
 * Etiquetadora.cpp
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#include "Etiquetadora.h"

Etiquetadora::Etiquetadora() {
	this->rectang = new RectangRef(1.0,1.0,2.0);
	this->cubeRef = new CubeRef(1.0,1.0,1.0);
}

void Etiquetadora::print(){
	glPushMatrix();
		glPushMatrix();
			glTranslatef(0.0,0.0,1.4);
			glScalef(0.5,0.5,0.6);
			cubeRef->print();
		glPopMatrix();
		glTranslatef(0.0,0.0,0.4);
		glScalef(0.3,0.3,0.4);
		cubeRef->print();
	glPopMatrix();
}

Etiquetadora::~Etiquetadora() {
	// TODO Auto-generated destructor stub
}

