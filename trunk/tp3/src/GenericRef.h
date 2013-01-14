/*
 * GenericRef.h
 *
 *  Created on: 27/01/2012
 *      Author: damian
 */

#ifndef GENERICREF_H_
#define GENERICREF_H_

#include "CubeMapProgram.h"

class GenericRef {
public:
	GenericRef(int cantTriangulos, float* positionArray, float* colorArray, float* normalArray, float* textureArray);
	void print();
	virtual ~GenericRef();

private:
	int texId;
	int cantTriangulos;
	float* positionArray;
	float* colorArray;
	float* normalArray;
	float* textureArray;
	CubeMapProgram* program;
	GLuint bufferPositionHandler;
	GLuint bufferColorHandler;
	GLuint bufferNormalHandler;
	GLuint bufferTextureHandler;
};

#endif /* GENERICREF_H_ */
