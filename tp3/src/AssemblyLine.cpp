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

	vector<Coordinate*>* section = new vector<Coordinate*>;
	section->push_back(new Coordinate(0.5,0,0));
	section->push_back(new Coordinate(0.5,0,-0.2));
	section->push_back(new Coordinate(-0.5,0,-0.2));
	section->push_back(new Coordinate(-0.5,0,0));
	section->push_back(new Coordinate(0.5,0,0));
	unsigned int sectionSize = section->size()-1;

	trianglesEstimated = (points->size()-1)*sectionSize*2;
	this->positionArray = new float[trianglesEstimated*9];
	this->colorArray = new float[trianglesEstimated*9];
	this->normalArray = new float[trianglesEstimated*9];
	this->textureArray = new float[trianglesEstimated*6];

	int posCounter = 0;
	int texPosCounter = 0;

	Coordinate* coordinate1 = new Coordinate(0,0,section->at(0)->getZ());
	Coordinate* coordinate2 = new Coordinate(0,0,section->at(1)->getZ());

	Coordinate* coordinate1New = new Coordinate(0,0,coordinate1->getZ());
	Coordinate* coordinate2New = new Coordinate(0,0,coordinate2->getZ());

	double deltaX;
	double deltaY;
	double norm;
	double tangentX;
	double tangentY;
	double normalX;

	for(unsigned int i = 0;i<size-1;i++){
		for(unsigned j = 0;j<sectionSize;j++){
			if(i!=0){
				deltaX = points->at(i)->getX()-points->at(i-1)->getX();
				deltaY = points->at(i)->getY()-points->at(i-1)->getY();
			}else{
				deltaX = points->at(i+1)->getX()-points->at(i)->getX();
				deltaY = points->at(i+1)->getY()-points->at(i)->getY();
			}

			norm = sqrt(pow(deltaX,2)+pow(deltaY,2));
			tangentX = deltaX / norm;
			tangentY = deltaY / norm;
			normalX = -tangentY;
			coordinate1->setX(points->at(i)->getX()+normalX*section->at(j)->getX());
			coordinate1->setY(points->at(i)->getY()+tangentX*section->at(j)->getX());
			coordinate1->setZ(section->at(j)->getZ());
			coordinate2->setX(points->at(i)->getX()+normalX*section->at(j+1)->getX());
			coordinate2->setY(points->at(i)->getY()+tangentX*section->at(j+1)->getX());
			coordinate2->setZ(section->at(j+1)->getZ());

			deltaX = points->at(i+1)->getX()-points->at(i)->getX();
			deltaY = points->at(i+1)->getY()-points->at(i)->getY();
			norm = sqrt(pow(deltaX,2)+pow(deltaY,2));
			tangentX = deltaX / norm;
			tangentY = deltaY / norm;
			normalX = -tangentY;
			coordinate1New->setX(points->at(i+1)->getX()+normalX*section->at(j)->getX());
			coordinate1New->setY(points->at(i+1)->getY()+tangentX*section->at(j)->getX());
			coordinate1New->setZ(section->at(j)->getZ());
			coordinate2New->setX(points->at(i+1)->getX()+normalX*section->at(j+1)->getX());
			coordinate2New->setY(points->at(i+1)->getY()+tangentX*section->at(j+1)->getX());
			coordinate2New->setZ(section->at(j+1)->getZ());

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
		}

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

