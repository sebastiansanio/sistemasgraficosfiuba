#ifndef BOTTLEGENERATOR_H_
#define BOTTLEGENERATOR_H_

#include "TextureProgram.h"
#include "Curves/Bezier.h"
#include <math.h>

class BottleGenerator{
public:
	static BottleGenerator* Instance();
	BottleGenerator();
	~BottleGenerator();
	void print();

private:
	static BottleGenerator* instance;
	float* positionArray;
	float* colorArray;
	float* normalArray;
	float* textureArray;
	GLuint bufferPositionHandler;
	GLuint bufferColorHandler;
	GLuint bufferNormalHandler;
	GLuint bufferTextureHandler;
	int trianglesEstimated;
	TextureProgram* program;

};


#endif
