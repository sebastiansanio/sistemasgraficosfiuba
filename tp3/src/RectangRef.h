/*
 * RectangRef.h
 *
 *  Created on: 27/01/2012
 *      Author: damian
 */

#ifndef RECTANGREF_H_
#define RECTANGREF_H_

#include "CubeMapProgram.h"
#include "GenericRef.h"

class RectangRef {
public:
	RectangRef(float xSize, float ySize,double tamTex);
	void print();
	virtual ~RectangRef();

private:
	GenericRef* genericRef;
};

#endif /* RECTANGREF_H_ */
