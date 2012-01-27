/*
 * Cube.h
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#ifndef CUBETEX_H_
#define CUBETEX_H_

#include "BasicProgram.h"
#include "TextureProgram.h"
#include "Rectang.h"

class CubeTex {
public:
	CubeTex(float xSize, float ySize, float zSize, int texId);
	void print();
	virtual ~CubeTex();

private:
	float x;
	float y;
	float z;
	int texId;
	TextureProgram* program;

	void drawRectangule();
};

#endif /* CUBETEX_H_ */
