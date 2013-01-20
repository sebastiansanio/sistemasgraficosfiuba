#ifndef BOTTLEDISPATCHER_H_
#define BOTTLEDISPATCHER_H_

#include "CubeMapProgram.h"
#include "TextureProgram.h"
#include "Curves/Bezier.h"
#include <math.h>

class BottleDispatcher{
public:
	static BottleDispatcher* Instance();
	BottleDispatcher();
	~BottleDispatcher();
	void print();

private:
	TextureProgram* program;
	static BottleDispatcher* instance;
	float* positionArray;
	float* colorArray;
	float* normalArray;
	float* textureArray;
	GLuint bufferPositionHandler;
	GLuint bufferColorHandler;
	GLuint bufferNormalHandler;
	GLuint bufferTextureHandler;
	int trianglesEstimated;

};


#endif
