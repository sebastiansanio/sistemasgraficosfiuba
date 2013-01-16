/*
 * AssemblyLine.cpp
 *
 *  Created on: 16/01/2013
 *      Author: Sebastián
 */

#include "AssemblyLine.h"


AssemblyLine::AssemblyLine(){
	program = AssemblyLineProgram::Instance();
	BSpline* bspline = new BSpline();
	bspline->addPoint(0,0,0);
	bspline->addPoint(0,1,0);
	bspline->addPoint(1,1,0);
	bspline->addPoint(1,0,0);
	bspline->addPoint(0,0,0);
	bspline->addPoint(0,1,0);

	bspline->calculate();

	vector<Coordinate*>* points= bspline->getPoints();
	unsigned int size = points->size();

	trianglesEstimated = points->size();

	this->positionArray = new float[trianglesEstimated*9];
	this->colorArray = new float[trianglesEstimated*9];
	this->normalArray = new float[trianglesEstimated*9];
	this->textureArray = new float[trianglesEstimated*6];

	int posCounter = 0;
	int texPosCounter = 0;

	for(unsigned int i = 0;i<size;i++){
		positionArray[posCounter]=points->at(i)->getX();
		positionArray[posCounter+1]=points->at(i)->getY();
		positionArray[posCounter+2]=points->at(i)->getZ();

		posCounter = posCounter + 3;
	}


	glGenBuffers(1, &bufferPositionHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferPositionHandler);
	glBufferData( GL_ARRAY_BUFFER, (trianglesEstimated * 9) * sizeof (float), this->positionArray, GL_STATIC_DRAW );

	glGenBuffers(1, &bufferColorHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferColorHandler);
	glBufferData( GL_ARRAY_BUFFER, (trianglesEstimated * 9) * sizeof (float), this->colorArray, GL_STATIC_DRAW );

	glGenBuffers(1, &bufferNormalHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferNormalHandler);
	glBufferData( GL_ARRAY_BUFFER, (trianglesEstimated * 9) * sizeof (float), this->normalArray, GL_STATIC_DRAW );

	glGenBuffers(1, &bufferTextureHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferTextureHandler);
	glBufferData( GL_ARRAY_BUFFER, (trianglesEstimated * 6) * sizeof (float), this->textureArray, GL_STATIC_DRAW );

}

void AssemblyLine::print(){
	program->setTexture(14);
	program->setActualProgram();

	glBindBuffer( GL_ARRAY_BUFFER, bufferNormalHandler);
	glVertexAttribPointer( VERTEX_NOR_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferColorHandler);
	glVertexAttribPointer( VERTEX_COL_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferPositionHandler);
	glVertexAttribPointer( VERTEX_POS_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferTextureHandler);
	glVertexAttribPointer( VERTEX_TEX_ATTR_INDEX, 2 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glDrawArrays( GL_POINTS, 0, trianglesEstimated * 3);

}

AssemblyLine::~AssemblyLine(){

}

