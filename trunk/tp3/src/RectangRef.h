/*
 * RectangRef.h
 *
 *  Created on: 27/01/2012
 *      Author: damian
 */

#ifndef RECTANGREF_H_
#define RECTANGREF_H_

#include "CubeMapProgram.h"

class RectangRef {
public:
	RectangRef(float xSize, float ySize,double tamTex);
	void print();
	virtual ~RectangRef();

private:
	float x;
	float y;
	int texId;
	double tamTex;
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

#endif /* RECTANGREF_H_ */
