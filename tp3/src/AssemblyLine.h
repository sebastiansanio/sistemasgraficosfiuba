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
#include "BottleInstance.h"
#include "Etiquetadora.h"
#include <math.h>

class AssemblyLine{
public:
	AssemblyLine();
	~AssemblyLine();
	void print();
	void advance();
	void addBottle();
	void drawBottles();

private:
	int bottlesQuantity;
	double labelerPosition;
	double fillerPosition;
	vector<Coordinate*>* points;
	vector<double>* pointsDistance;
	vector<BottleInstance*>* bottles;
	void calculateDistances();
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
	Etiquetadora* etiquetadora;
	bool etiquetando;
};



#endif /* ASSEMBLYLINE_H_ */
