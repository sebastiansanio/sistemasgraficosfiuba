/*
 * ObservadorCaminante.h
 *
 *  Created on: Jan 15, 2013
 *      Author: damian
 */

#ifndef OBSERVADORCAMINANTE_H_
#define OBSERVADORCAMINANTE_H_

#include "Observador.h"

class ObservadorCaminante: public Observador {
public:
	ObservadorCaminante();
	void upz();
	void downz();
	void left();
	void right();
	void forward();
	void backward();
	void rotate(float angleX, float angleY);
	virtual ~ObservadorCaminante();

private:
	float anguloX;
	float anguloY;
};

#endif /* OBSERVADORCAMINANTE_H_ */
