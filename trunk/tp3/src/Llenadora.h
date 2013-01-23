/*
 * Llenadora.h
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#ifndef LLENADORA_H_
#define LLENADORA_H_

#include "CubeRef.h"
#include "PortaEtiqueta.h"

class Llenadora {
public:
	Llenadora();
	void print();
	void start();
	void mover();
	virtual ~Llenadora();

private:
	CubeRef* cubeRef;
	Generic* tanque;
	Generic* cilindro;
	Generic* toroide;
	float posLlenadora;
	int tiempoRestante;
	bool moviendo;
	bool subiendo;
};

#endif /* LLENADORA_H_ */
