#ifndef BOTTLE_H_
#define BOTTLE_H_

#include "BasicProgram.h"
#include "BottleProgram.h"
#include "TextureProgram.h"
#include "Curves/Bezier.h"
#include <math.h>

class Bottle{
public:
	static Bottle* Instance();
	Bottle();
	~Bottle();
	void print(double liquidHeight,bool label);
	void printPack();
	double getFilledHeight();
private:
	double filledHeight;
	static Bottle* instance;
	Coordinate* calculateNormal(vector<Coordinate*>* points,unsigned int i,float j);
	float* positionArray;
	float* colorArray;
	float* normalArray;
	float* textureArray;
	GLuint bufferPositionHandler;
	GLuint bufferColorHandler;
	GLuint bufferNormalHandler;
	GLuint bufferTextureHandler;
	int trianglesEstimated;
	BottleProgram* program;
	Bezier* bezier;
};


#endif /* BOTTLE_H_ */
