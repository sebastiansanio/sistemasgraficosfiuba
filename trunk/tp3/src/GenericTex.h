/*
 * GenericTex.h
 *
 *  Created on: Jan 16, 2013
 *      Author: damian
 */

#ifndef GENERICTEX_H_
#define GENERICTEX_H_

#include "TextureProgram.h"

class GenericTex {
public:
	GenericTex(int cantTriangulos, float* positionArray, float* colorArray, float* normalArray, float* textureArray, int textId);
	void print();
	virtual ~GenericTex();

private:
	int texId;
	int cantTriangulos;
	float* positionArray;
	float* colorArray;
	float* normalArray;
	float* textureArray;
	TextureProgram* program;
	GLuint bufferPositionHandler;
	GLuint bufferColorHandler;
	GLuint bufferNormalHandler;
	GLuint bufferTextureHandler;
};

#endif /* GENERICTEX_H_ */
