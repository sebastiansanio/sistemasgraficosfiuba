/*
 * Cube.h
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#ifndef CUBEREF_H_
#define CUBEREF_H_

#include "RectangRef.h"

class CubeRef {
public:
	CubeRef(float xSize, float ySize, float zSize);
	void print();
	virtual ~CubeRef();

private:
	float x;
	float y;
	float z;
	RectangRef* rectang;
};

#endif /* CUBEREF_H_ */
