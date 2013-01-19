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
#include "AssemblyLineProgram.h"
#include "Curves/BSpline.h"
#include <math.h>

class AssemblyLine{
public:
	AssemblyLine();
	~AssemblyLine();
	void print();

private:
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
	AssemblyLineProgram* program;
	BSpline* bezier;
	void rotate(Coordinate* coordinate, double angle);
};



#endif /* ASSEMBLYLINE_H_ */
