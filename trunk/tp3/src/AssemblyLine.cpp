/*
 * AssemblyLine.cpp
 *
 *  Created on: 16/01/2013
 *      Author: Sebastián
 */

#include "AssemblyLine.h"



void AssemblyLine::rotate(Coordinate* coordinate, double angle){


	double x = coordinate->getX();
	double y = coordinate->getY();
	coordinate->setX(x * cos(angle) - (y* sin(angle)));
	coordinate->setY(y * sin(angle) + (y* cos(angle)));

}


AssemblyLine::AssemblyLine(){

	program = AssemblyLineProgram::Instance();
	BSpline* bspline = new BSpline();
	bspline->addPoint(0,-2,0);
	bspline->addPoint(5,2,0);
	bspline->addPoint(0,4,0);
	bspline->addPoint(-5,6,0);
	bspline->addPoint(0,8,0);


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

	Coordinate*  coordinate1= new Coordinate(0.5,0,0);
	Coordinate*  coordinate2= new Coordinate(0.5,0,0.2);
	Coordinate*  coordinate3= new Coordinate(-0.5,0,0.2);
	Coordinate*  coordinate4= new Coordinate(-0.5,0,0);
	Coordinate* coordinate1New = new Coordinate(coordinate1->getX(),coordinate1->getY(),coordinate1->getZ());
	Coordinate* coordinate2New = new Coordinate(coordinate2->getX(),coordinate2->getY(),coordinate2->getZ());
	Coordinate* coordinate3New = new Coordinate(coordinate3->getX(),coordinate3->getY(),coordinate3->getZ());
	Coordinate* coordinate4New = new Coordinate(coordinate4->getX(),coordinate4->getY(),coordinate4->getZ());

	for(unsigned int i = 0;i<size-1;i++){

		double deltaX = points->at(i+1)->getX()-points->at(i)->getX();
		double deltaY = points->at(i+1)->getY()-points->at(i)->getY();
		double angle = atan(deltaY/deltaX);


		coordinate1New->setX(coordinate1New->getX()+deltaX);
		coordinate1New->setY(coordinate1New->getY()+deltaY);
		coordinate2New->setX(coordinate2New->getX()+deltaX);
		coordinate2New->setY(coordinate2New->getY()+deltaY);
		coordinate3New->setX(coordinate3New->getX()+deltaX);
		coordinate3New->setY(coordinate3New->getY()+deltaY);
		coordinate4New->setX(coordinate4New->getX()+deltaX);
		coordinate4New->setY(coordinate4New->getY()+deltaY);

//		rotate(coordinate1New,angle);
//		rotate(coordinate2New,angle);
//		rotate(coordinate3New,angle);
//		rotate(coordinate4New,angle);


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


		coordinate1->setX(coordinate1New->getX());
		coordinate1->setY(coordinate1New->getY());
		coordinate2->setX(coordinate2New->getX());
		coordinate2->setY(coordinate2New->getY());
		coordinate3->setX(coordinate3New->getX());
		coordinate3->setY(coordinate3New->getY());
		coordinate4->setX(coordinate4New->getX());
		coordinate4->setY(coordinate4New->getY());
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

