#ifndef BOTTLELABELER_H_
#define BOTTLELABELER_H_

#include "TextureProgram.h"
#include "Curves/Bezier.h"
#include "BottleInstance.h"
#include <math.h>

class BottleLabeler{
public:
	static BottleLabeler* Instance();
	BottleLabeler();
	~BottleLabeler();
	void print();
	bool label(BottleInstance* bottle);
private:
	double labelTime;
	static BottleLabeler* instance;
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
