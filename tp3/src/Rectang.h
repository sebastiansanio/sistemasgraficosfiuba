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
	Rectang(float xSize, float ySize,double tamPaso);
	void print();
	virtual ~Rectang();

private:
	float x;
	float y;
	double tamPaso;
	int cantTriangulos;
	float* positionArray;
	float* colorArray;
	float* normalArray;
	BasicProgram* program;
	GLuint bufferPositionHandler;
	GLuint bufferColorHandler;
	GLuint bufferNormalHandler;
};

#endif /* RECTANGLE_H_ */
