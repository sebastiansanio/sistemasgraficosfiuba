/*
 * Etiquetadora.h
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#ifndef ETIQUETADORA_H_
#define ETIQUETADORA_H_

#include "CubeRef.h"

class Etiquetadora {
public:
	Etiquetadora();
	void print();
	virtual ~Etiquetadora();

private:
	RectangRef* rectang;
	CubeRef* cubeRef;
};

#endif /* CUBEREF_H_ */
