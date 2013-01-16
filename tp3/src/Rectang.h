/*
 * Rectangle.h
 *
 *  Created on: 27/01/2012
 *      Author: damian
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Generic.h"

class Rectang {
public:
	Rectang(float xSize, float ySize,double tamPaso);
	void print();
	virtual ~Rectang();

private:
	Generic* generic;
};

#endif /* RECTANGLE_H_ */
