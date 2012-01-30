/*
 * Cube.h
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#ifndef CUBEREF_H_
#define CUBEREF_H_

#include "BasicProgram.h"
#include "CubeMapProgram.h"
#include "Rectang.h"

class CubeRef {
public:
	CubeRef(float xSize, float ySize, float zSize);
	void print();
	virtual ~CubeRef();

private:
	float x;
	float y;
	float z;
	int texId;
	CubeMapProgram* program;

	void drawRectangule();
};

#endif /* CUBEREF_H_ */
