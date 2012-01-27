/*
 * Cube.h
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "BasicProgram.h"
#include "TextureProgram.h"

class Cube {
public:
	Cube(float xSize, float ySize, float zSize, int texId);
	void print();
	virtual ~Cube();

private:
	float x;
	float y;
	float z;
	int texId;
	TextureProgram* program;

	void drawRectangule();
};

#endif /* CUBE_H_ */
