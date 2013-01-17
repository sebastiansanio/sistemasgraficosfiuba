/*
 * AssemblyLine.cpp
 *
 *  Created on: 16/01/2013
 *      Author: Sebastián
 */

#include "AssemblyLine.h"


AssemblyLine::AssemblyLine(){

	Coordinate*  coordinate1= new Coordinate(0.5,0,0);
	Coordinate*  coordinate2= new Coordinate(0.5,0,0.2);
	Coordinate*  coordinate3= new Coordinate(-0.5,0,0.2);
	Coordinate*  coordinate4= new Coordinate(-0.5,0,0);


	program = AssemblyLineProgram::Instance();
	BSpline* bspline = new BSpline();
	bspline->addPoint(0,0,0);
	bspline->addPoint(0,2,0);
	bspline->addPoint(0,4,0);
	bspline->addPoint(0,6,0);


	bspline->calculate();

	vector<Coordinate*>* points= bspline->getPoints();

	unsigned int size = points->size();

	trianglesEstimated = (points->size()-1)*8;

	this->positionArray = new float[trianglesEstimated*9];
	this->colorArray = new float[trianglesEstimated*9];
	this->normalArray = new float[trianglesEstimated*9];
	this->textureArray = new float[trianglesEstimated*6];

	int posCounter = 0;
	int texPosCounter = 0;

	for(unsigned int i = 0;i<size-1;i++){

		double deltaX = points->at(i+1)->getX()-points->at(i)->getX();
		double deltaY = points->at(i+1)->getY()-points->at(i)->getY();
		Coordinate* coordinate1New = new Coordinate(coordinate1->getX()+deltaX,coordinate1->getY()+deltaY,coordinate1->getZ());
		Coordinate* coordinate2New = new Coordinate(coordinate2->getX()+deltaX,coordinate2->getY()+deltaY,coordinate2->getZ());
		Coordinate* coordinate3New = new Coordinate(coordinate3->getX()+deltaX,coordinate3->getY()+deltaY,coordinate3->getZ());
		Coordinate* coordinate4New = new Coordinate(coordinate4->getX()+deltaX,coordinate4->getY()+deltaY,coordinate4->getZ());

		positionArray[posCounter]=coordinate1->getX();
		positionArray[posCounter+1]=coordinate1->getY();
		positionArray[posCounter+2]=coordinate1->getZ();
		positionArray[posCounter+3]=coordinate2New->getX();
		positionArray[posCounter+4]=coordinate2New->getY();
		positionArray[posCounter+5]=coordinate2New->getZ();
		positionArray[posCounter+6]=coordinate1New->getX();
		positionArray[posCounter+7]=coordinate1New->getY();
		positionArray[posCounter+8]=coordinate1New->getZ();
		posCounter = posCounter + 9;

		positionArray[posCounter]=coordinate1->getX();
		positionArray[posCounter+1]=coordinate1->getY();
		positionArray[posCounter+2]=coordinate1->getZ();
		positionArray[posCounter+3]=coordinate2New->getX();
		positionArray[posCounter+4]=coordinate2New->getY();
		positionArray[posCounter+5]=coordinate2New->getZ();
		positionArray[posCounter+6]=coordinate2->getX();
		positionArray[posCounter+7]=coordinate2->getY();
		positionArray[posCounter+8]=coordinate2->getZ();
		posCounter = posCounter + 9;

		positionArray[posCounter]=coordinate2->getX();
		positionArray[posCounter+1]=coordinate2->getY();
		positionArray[posCounter+2]=coordinate2->getZ();
		positionArray[posCounter+3]=coordinate3New->getX();
		positionArray[posCounter+4]=coordinate3New->getY();
		positionArray[posCounter+5]=coordinate3New->getZ();
		positionArray[posCounter+6]=coordinate2New->getX();
		positionArray[posCounter+7]=coordinate2New->getY();
		positionArray[posCounter+8]=coordinate2New->getZ();
		posCounter = posCounter + 9;

		positionArray[posCounter]=coordinate2->getX();
		positionArray[posCounter+1]=coordinate2->getY();
		positionArray[posCounter+2]=coordinate2->getZ();
		positionArray[posCounter+3]=coordinate3New->getX();
		positionArray[posCounter+4]=coordinate3New->getY();
		positionArray[posCounter+5]=coordinate3New->getZ();
		positionArray[posCounter+6]=coordinate3->getX();
		positionArray[posCounter+7]=coordinate3->getY();
		positionArray[posCounter+8]=coordinate3->getZ();
		posCounter = posCounter + 9;

		positionArray[posCounter]=coordinate3->getX();
		positionArray[posCounter+1]=coordinate3->getY();
		positionArray[posCounter+2]=coordinate3->getZ();
		positionArray[posCounter+3]=coordinate4New->getX();
		positionArray[posCounter+4]=coordinate4New->getY();
		positionArray[posCounter+5]=coordinate4New->getZ();
		positionArray[posCounter+6]=coordinate3New->getX();
		positionArray[posCounter+7]=coordinate3New->getY();
		positionArray[posCounter+8]=coordinate3New->getZ();
		posCounter = posCounter + 9;

		positionArray[posCounter]=coordinate3->getX();
		positionArray[posCounter+1]=coordinate3->getY();
		positionArray[posCounter+2]=coordinate3->getZ();
		positionArray[posCounter+3]=coordinate4New->getX();
		positionArray[posCounter+4]=coordinate4New->getY();
		positionArray[posCounter+5]=coordinate4New->getZ();
		positionArray[posCounter+6]=coordinate4->getX();
		positionArray[posCounter+7]=coordinate4->getY();
		positionArray[posCounter+8]=coordinate4->getZ();
		posCounter = posCounter + 9;

		positionArray[posCounter]=coordinate4->getX();
		positionArray[posCounter+1]=coordinate4->getY();
		positionArray[posCounter+2]=coordinate4->getZ();
		positionArray[posCounter+3]=coordinate1New->getX();
		positionArray[posCounter+4]=coordinate1New->getY();
		positionArray[posCounter+5]=coordinate1New->getZ();
		positionArray[posCounter+6]=coordinate4New->getX();
		positionArray[posCounter+7]=coordinate4New->getY();
		positionArray[posCounter+8]=coordinate4New->getZ();
		posCounter = posCounter + 9;

		positionArray[posCounter]=coordinate4->getX();
		positionArray[posCounter+1]=coordinate4->getY();
		positionArray[posCounter+2]=coordinate4->getZ();
		positionArray[posCounter+3]=coordinate1New->getX();
		positionArray[posCounter+4]=coordinate1New->getY();
		positionArray[posCounter+5]=coordinate1New->getZ();
		positionArray[posCounter+6]=coordinate1->getX();
		positionArray[posCounter+7]=coordinate1->getY();
		positionArray[posCounter+8]=coordinate1->getZ();
		posCounter = posCounter + 9;


		coordinate1 = coordinate1New;
		coordinate2 = coordinate2New;
		coordinate3 = coordinate3New;
		coordinate4 = coordinate4New;
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

	glDrawArrays( GL_TRIANGLES, 0, trianglesEstimated * 3);

}

AssemblyLine::~AssemblyLine(){

}

