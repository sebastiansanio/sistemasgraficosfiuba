/*
 * Observador.h
 *
 *  Created on: Jan 15, 2013
 *      Author: damian
 */

#ifndef OBSERVADOR_H_
#define OBSERVADOR_H_

#include <math.h>

class Observador {
public:
	Observador();
	virtual ~Observador();
	void upz();
	void downz();
	void left();
	void right();
	void forward();
	void backward();
	float* getEye();
	float* getAt();
	float* getUp();

protected:
	float ratio;
	float anglehor;
	float anglevert;
	float eye[3];
	float at[3];
	float up[3];
	void calcPosition();
};

#endif /* OBSERVADOR_H_ */
