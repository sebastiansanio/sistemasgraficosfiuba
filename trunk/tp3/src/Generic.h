/*
 * Generic.h
 *
 *  Created on: Jan 16, 2013
 *      Author: damian
 */

#ifndef GENERIC_H_
#define GENERIC_H_

#include "BasicProgram.h"

class Generic {
public:
	Generic(int cantTriangulos, float* positionArray, float* colorArray, float* normalArray);
	void print();
	virtual ~Generic();

private:
	int cantTriangulos;
	float* positionArray;
	float* colorArray;
	float* normalArray;
	BasicProgram* program;
	GLuint bufferPositionHandler;
	GLuint bufferColorHandler;
	GLuint bufferNormalHandler;
};

#endif /* GENERIC_H_ */
