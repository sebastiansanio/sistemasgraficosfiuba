/*
 * AssemblyLine.h
 *
 *  Created on: 16/01/2013
 *      Author: Sebastián
 */

#ifndef ASSEMBLYLINE_H_
#define ASSEMBLYLINE_H_

#include "BasicProgram.h"
#include "TextureProgram.h"
#include "Curves/BSpline.h"
#include <math.h>

class AssemblyLine{
public:
	AssemblyLine();
	~AssemblyLine();
	void print();
	void advance(double speed);

private:
	void setTexture();
	Coordinate* calculateNormal(vector<Coordinate*>* points,unsigned int j);
	unsigned int size;
	unsigned int sectionSize;
	double advanceParameter;
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
	BSpline* bezier;
};



#endif /* ASSEMBLYLINE_H_ */
