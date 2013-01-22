/*
 * Etiquetadora.h
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#ifndef ETIQUETADORA_H_
#define ETIQUETADORA_H_

#include "CubeRef.h"
#include "PortaEtiqueta.h"

class Etiquetadora {
public:
	Etiquetadora();
	void print();
	void start();
	void mover();
	virtual ~Etiquetadora();

private:
	CubeRef* cubeRef;
	PortaEtiqueta* portaEtiqueta;
	float posEtiquetadora;
	bool moviendo;
	bool subiendo;
};

#endif /* CUBEREF_H_ */
