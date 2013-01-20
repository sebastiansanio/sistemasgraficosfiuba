#ifndef RAMP_H_
#define RAMP_H_

#include "CubeMapProgram.h"
#include "TextureProgram.h"
#include "Curves/Bezier.h"
#include <math.h>

class Ramp{
public:
	static Ramp* Instance();
	Ramp(double height,double width,double length);
	~Ramp();
	void print();

private:
	TextureProgram* program;
	static Ramp* instance;
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
