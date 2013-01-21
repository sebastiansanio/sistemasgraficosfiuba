/*
 * PortaEtiqueta.h
 *
 *  Created on: Jan 16, 2013
 *      Author: damian
 */

#ifndef PORTAETIQUETA_H_
#define PORTAETIQUETA_H_

#include <vector>
#include "Curves/Coordinate.h"
#include "Generic.h"

class PortaEtiqueta {
public:
	PortaEtiqueta();
	void print();
	virtual ~PortaEtiqueta();

private:
	Generic* generic;
};

#endif /* PORTAETIQUETA_H_ */
