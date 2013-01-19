/*
 * AssemblyLine.cpp
 *
 *  Created on: 16/01/2013
 *      Author: Sebastián
 */

#include "AssemblyLine.h"
#define PI 3.14159265


void AssemblyLine::rotate(Coordinate* coordinate, double angle){


	double x = coordinate->getX();
	double y = coordinate->getY();
	coordinate->setX(x * cos(angle));
	coordinate->setY(y * sin(angle));

}


AssemblyLine::AssemblyLine(){

	program = TextureProgram::Instance();
	BSpline* bspline = new BSpline();
	bspline->addPoint(-5,-5,0);
	bspline->addPoint(-5,5,0);
	bspline->addPoint(0,5,0);
	bspline->addPoint(5,5,0);
	bspline->addPoint(5,-5,0);

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

	Coordinate* coordinate1 = new Coordinate(0,0,0.2);
	Coordinate* coordinate2 = new Coordinate(0,0,0);
	Coordinate* coordinate3 = new Coordinate(0,0,0);
	Coordinate* coordinate4 = new Coordinate(0,0,0.2);

	Coordinate* coordinate1New = new Coordinate(0,0,coordinate1->getZ());
	Coordinate* coordinate2New = new Coordinate(0,0,coordinate2->getZ());
	Coordinate* coordinate3New = new Coordinate(0,0,coordinate3->getZ());
	Coordinate* coordinate4New = new Coordinate(0,0,coordinate4->getZ());

	double deltaX = points->at(1)->getX()-points->at(0)->getX();
	double deltaY = points->at(1)->getY()-points->at(0)->getY();
	double norm = sqrt(pow(deltaX,2)+pow(deltaY,2));
	double tangentX = deltaX / norm;
	double tangentY = deltaY / norm;

	double normalX = -tangentY;
	double normalY = tangentX;


	coordinate1->setX(points->at(0)->getX()+normalX*0.5);
	coordinate1->setY(points->at(0)->getY()+tangentX*0.5);
	coordinate2->setX(points->at(0)->getX()+normalX*0.5);
	coordinate2->setY(points->at(0)->getY()+tangentX*0.5);
	coordinate3->setX(points->at(0)->getX()-normalX*0.5);
	coordinate3->setY(points->at(0)->getY()-tangentX*0.5);
	coordinate4->setX(points->at(0)->getX()-normalX*0.5);
	coordinate4->setY(points->at(0)->getY()-tangentX*0.5);



	for(unsigned int i = 0;i<size-1;i++){

		deltaX = points->at(i+1)->getX()-points->at(i)->getX();
		deltaY = points->at(i+1)->getY()-points->at(i)->getY();
		norm = sqrt(pow(deltaX,2)+pow(deltaY,2));
		tangentX = deltaX / norm;
		tangentY = deltaY / norm;

		normalX = -tangentY;
		normalY = tangentX;

		coordinate1New->setX(points->at(i+1)->getX()+normalX*0.5);
		coordinate1New->setY(points->at(i+1)->getY()+tangentX*0.5);
		coordinate2New->setX(points->at(i+1)->getX()+normalX*0.5);
		coordinate2New->setY(points->at(i+1)->getY()+tangentX*0.5);
		coordinate3New->setX(points->at(i+1)->getX()-normalX*0.5);
		coordinate3New->setY(points->at(i+1)->getY()-tangentX*0.5);
		coordinate4New->setX(points->at(i+1)->getX()-normalX*0.5);
		coordinate4New->setY(points->at(i+1)->getY()-tangentX*0.5);

		positionArray[posCounter]=coordinate1->getX();
		positionArray[posCounter+1]=coordinate1->getY();
		positionArray[posCounter+2]=coordinate1->getZ();
		positionArray[posCounter+3]=coordinate2New->getX();
		positionArray[posCounter+4]=coordinate2New->getY();
		positionArray[posCounter+5]=coordinate2New->getZ();
		positionArray[posCounter+6]=coordinate1New->getX();
		positionArray[posCounter+7]=coordinate1New->getY();
		positionArray[posCounter+8]=coordinate1New->getZ();
		normalArray[posCounter]=0;
		normalArray[posCounter+1]=0;
		normalArray[posCounter+2]=1;
		normalArray[posCounter+3]=0;
		normalArray[posCounter+4]=0;
		normalArray[posCounter+5]=1;
		normalArray[posCounter+6]=0;
		normalArray[posCounter+7]=0;
		normalArray[posCounter+8]=1;
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
		normalArray[posCounter]=0;
		normalArray[posCounter+1]=0;
		normalArray[posCounter+2]=1;
		normalArray[posCounter+3]=0;
		normalArray[posCounter+4]=0;
		normalArray[posCounter+5]=1;
		normalArray[posCounter+6]=0;
		normalArray[posCounter+7]=0;
		normalArray[posCounter+8]=1;
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
		normalArray[posCounter]=0;
		normalArray[posCounter+1]=0;
		normalArray[posCounter+2]=1;
		normalArray[posCounter+3]=0;
		normalArray[posCounter+4]=0;
		normalArray[posCounter+5]=1;
		normalArray[posCounter+6]=0;
		normalArray[posCounter+7]=0;
		normalArray[posCounter+8]=1;
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
		normalArray[posCounter]=0;
		normalArray[posCounter+1]=0;
		normalArray[posCounter+2]=1;
		normalArray[posCounter+3]=0;
		normalArray[posCounter+4]=0;
		normalArray[posCounter+5]=1;
		normalArray[posCounter+6]=0;
		normalArray[posCounter+7]=0;
		normalArray[posCounter+8]=1;
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
		normalArray[posCounter]=0;
		normalArray[posCounter+1]=0;
		normalArray[posCounter+2]=1;
		normalArray[posCounter+3]=0;
		normalArray[posCounter+4]=0;
		normalArray[posCounter+5]=1;
		normalArray[posCounter+6]=0;
		normalArray[posCounter+7]=0;
		normalArray[posCounter+8]=1;
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
		normalArray[posCounter]=0;
		normalArray[posCounter+1]=0;
		normalArray[posCounter+2]=1;
		normalArray[posCounter+3]=0;
		normalArray[posCounter+4]=0;
		normalArray[posCounter+5]=1;
		normalArray[posCounter+6]=0;
		normalArray[posCounter+7]=0;
		normalArray[posCounter+8]=1;
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
		normalArray[posCounter]=0;
		normalArray[posCounter+1]=0;
		normalArray[posCounter+2]=1;
		normalArray[posCounter+3]=0;
		normalArray[posCounter+4]=0;
		normalArray[posCounter+5]=1;
		normalArray[posCounter+6]=0;
		normalArray[posCounter+7]=0;
		normalArray[posCounter+8]=1;
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
		normalArray[posCounter]=0;
		normalArray[posCounter+1]=0;
		normalArray[posCounter+2]=1;
		normalArray[posCounter+3]=0;
		normalArray[posCounter+4]=0;
		normalArray[posCounter+5]=1;
		normalArray[posCounter+6]=0;
		normalArray[posCounter+7]=0;
		normalArray[posCounter+8]=1;
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

