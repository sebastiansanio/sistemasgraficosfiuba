/*
 * RectangTex.h
 *
 *  Created on: 27/01/2012
 *      Author: damian
 */

#ifndef RECTANGTEX_H_
#define RECTANGTEX_H_

#include "GenericTex.h"

class RectangTex {
public:
	RectangTex(float xSize, float ySize, int texId,double tamTex);
	void print();
	virtual ~RectangTex();

private:
	GenericTex* genericTex;
//	float x;
//	float y;
//	int texId;
//	double tamTex;
//	int cantTriangulos;
//	float* positionArray;
//	float* colorArray;
//	float* normalArray;
//	float* textureArray;
//	TextureProgram* program;
//	GLuint bufferPositionHandler;
//	GLuint bufferColorHandler;
//	GLuint bufferNormalHandler;
//	GLuint bufferTextureHandler;
};

#endif /* RECTANGTEX_H_ */
