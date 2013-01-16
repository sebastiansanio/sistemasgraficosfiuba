/*
 * ObservadorCentro.h
 *
 *  Created on: Jan 15, 2013
 *      Author: damian
 */

#ifndef OBSERVADORCENTRO_H_
#define OBSERVADORCENTRO_H_

#include "Observador.h"

class ObservadorCentro : public Observador {
public:
	ObservadorCentro();
	void upz();
	void downz();
	void left();
	void right();
	void forward();
	void backward();
	virtual ~ObservadorCentro();

private:
	float ratio;
	float anglehor;
	float anglevert;
	void calcPosition();
};

#endif /* OBSERVADORCENTRO_H_ */
