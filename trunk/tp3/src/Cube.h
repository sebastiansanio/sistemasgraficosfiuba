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
	Cube(float xSize, float ySize, float zSize);
	void print();
	virtual ~Cube();

private:
	float x;
	float y;
	float z;
	TextureProgram* program;
	BitMap* piso;

	void drawRectangule();
};

#endif /* CUBE_H_ */
