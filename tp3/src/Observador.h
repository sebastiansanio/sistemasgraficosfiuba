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
	virtual void upz();
	virtual void downz();
	virtual void left();
	virtual void right();
	virtual void forward();
	virtual void backward();
	virtual void rotate(float angleX, float angleY);
	float* getEye();
	float* getAt();
	float* getUp();

protected:
	float eye[3];
	float at[3];
	float up[3];
};

#endif /* OBSERVADOR_H_ */
