/*
 * Rectangle.h
 *
 *  Created on: 27/01/2012
 *      Author: damian
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "BasicProgram.h"

class Rectang {
public:
	Rectang(float xSize, float ySize);
	void print();
	virtual ~Rectang();

private:
	float x;
	float y;
	BasicProgram* program;
};

#endif /* RECTANGLE_H_ */
