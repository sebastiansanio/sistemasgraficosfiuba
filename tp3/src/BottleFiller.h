#ifndef BOTTLEFILLER_H_
#define BOTTLEFILLER_H_

#include "TextureProgram.h"
#include "Curves/Bezier.h"
#include <math.h>

class BottleFiller{
public:
	static BottleFiller* Instance();
	BottleFiller();
	~BottleFiller();
	void print();

private:
	static BottleFiller* instance;
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
