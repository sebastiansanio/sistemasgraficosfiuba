/*
 * RectangTex.h
 *
 *  Created on: 27/01/2012
 *      Author: damian
 */

#ifndef RECTANGTEX_H_
#define RECTANGTEX_H_

#include "BasicProgram.h"
#include "TextureProgram.h"

class RectangTex {
public:
	RectangTex(float xSize, float ySize, int texId);
	void print();
	virtual ~RectangTex();

private:
	float x;
	float y;
	int texId;
	TextureProgram* program;
};

#endif /* RECTANGTEX_H_ */
