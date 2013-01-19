/*
 * AssemblyLine.cpp
 *
 *  Created on: 16/01/2013
 *      Author: Sebastián
 */

#include "AssemblyLine.h"
#define PI 3.14159265


Coordinate* AssemblyLine::calculateNormal(vector<Coordinate*>* points,unsigned int j){
	int prevPoint;
	int actualPoint = j;
	if(j==0){
		prevPoint = points->size()-2;
	}else{
		prevPoint = j-1;
	}

	double deltaX = points->at(actualPoint)->getX()-points->at(prevPoint)->getX();
	double deltaZ = points->at(actualPoint)->getZ()-points->at(prevPoint)->getZ();
	double normalX = -deltaZ;
	double normalZ =  deltaX;

	Coordinate* normal = new Coordinate(normalX,0,normalZ);
	normal->normalize();
	return normal;
}

void AssemblyLine::advance(double speed){

	advanceParameter += speed;
}


void AssemblyLine::setTexture(){

	int texPosCounter = 0;
	for(unsigned int i = 0;i<size-1;i++){
		for(unsigned j = 0;j<sectionSize;j++){
			double horizontalParameterFrom;
			double horizontalParameterTo;
			if(j!=3){
				horizontalParameterFrom = 0;
				horizontalParameterTo = 0.1;
			}else{
				horizontalParameterFrom = 0.9;
				horizontalParameterTo = 1;
			}

			textureArray[texPosCounter+1]=horizontalParameterFrom;
			textureArray[texPosCounter]=0+advanceParameter;
			textureArray[texPosCounter+3]=horizontalParameterTo;
			textureArray[texPosCounter+2]=1+advanceParameter;
			textureArray[texPosCounter+5]=horizontalParameterFrom;
			textureArray[texPosCounter+4]=1+advanceParameter;
			texPosCounter = texPosCounter+6;

			textureArray[texPosCounter+1]=horizontalParameterFrom;
			textureArray[texPosCounter]=0+advanceParameter;
			textureArray[texPosCounter+3]=horizontalParameterTo;
			textureArray[texPosCounter+2]=1+advanceParameter;
			textureArray[texPosCounter+5]=horizontalParameterTo;
			textureArray[texPosCounter+4]=0+advanceParameter;
			texPosCounter = texPosCounter+6;
		}
	}
}

AssemblyLine::AssemblyLine(){

	advanceParameter = 0;

	program = TextureProgram::Instance();

	BSpline* bspline = new BSpline();
	bspline->addPoint(-7,-7,0);
	bspline->addPoint(-5,-7,0);
	bspline->addPoint(-5,5,0);
	bspline->addPoint(0,2,0);
	bspline->addPoint(2,5,0);
	bspline->addPoint(4,5,0);
	bspline->addPoint(6,2,0);
	bspline->calculate();
	vector<Coordinate*>* points= bspline->getPoints();
	size = points->size();

	vector<Coordinate*>* section = new vector<Coordinate*>;
	section->push_back(new Coordinate(-0.6,0,-0.2));
	section->push_back(new Coordinate(-0.6,0,0.2));
	section->push_back(new Coordinate(-0.5,0,0.2));
	section->push_back(new Coordinate(-0.5,0,0));
	section->push_back(new Coordinate(0.5,0,0));
	section->push_back(new Coordinate(0.5,0,0.2));
	section->push_back(new Coordinate(0.6,0,0.2));
	section->push_back(new Coordinate(0.6,0,-0.2));
	section->push_back(new Coordinate(-0.6,0,-0.2));
	sectionSize = section->size()-1;

	trianglesEstimated = (points->size()-1)*sectionSize*2;
	this->positionArray = new float[trianglesEstimated*9];
	this->colorArray = new float[trianglesEstimated*9];
	this->normalArray = new float[trianglesEstimated*9];
	this->textureArray = new float[trianglesEstimated*6];

	int posCounter = 0;
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
	double normalY;

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
			normalY = tangentX;
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
			normalY = tangentX;

			coordinate1New->setX(points->at(i+1)->getX()+normalX*section->at(j)->getX());
			coordinate1New->setY(points->at(i+1)->getY()+tangentX*section->at(j)->getX());
			coordinate1New->setZ(section->at(j)->getZ());
			coordinate2New->setX(points->at(i+1)->getX()+normalX*section->at(j+1)->getX());
			coordinate2New->setY(points->at(i+1)->getY()+tangentX*section->at(j+1)->getX());
			coordinate2New->setZ(section->at(j+1)->getZ());

			Coordinate* normal = new Coordinate(0,0,1);
			normal = calculateNormal(section,j+1);

			positionArray[posCounter]=coordinate1->getX();
			positionArray[posCounter+1]=coordinate1->getY();
			positionArray[posCounter+2]=coordinate1->getZ();
			positionArray[posCounter+3]=coordinate2New->getX();
			positionArray[posCounter+4]=coordinate2New->getY();
			positionArray[posCounter+5]=coordinate2New->getZ();
			positionArray[posCounter+6]=coordinate1New->getX();
			positionArray[posCounter+7]=coordinate1New->getY();
			positionArray[posCounter+8]=coordinate1New->getZ();
			normalArray[posCounter]=normal->getX()*normalX;
			normalArray[posCounter+1]=normal->getX()*normalY;
			normalArray[posCounter+2]=normal->getZ();
			normalArray[posCounter+3]=normal->getX()*normalX;
			normalArray[posCounter+4]=normal->getX()*normalY;
			normalArray[posCounter+5]=normal->getZ();
			normalArray[posCounter+6]=normal->getX()*normalX;
			normalArray[posCounter+7]=normal->getX()*normalY;
			normalArray[posCounter+8]=normal->getZ();
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
			normalArray[posCounter]=normal->getX()*normalX;
			normalArray[posCounter+1]=normal->getX()*normalY;
			normalArray[posCounter+2]=normal->getZ();
			normalArray[posCounter+3]=normal->getX()*normalX;
			normalArray[posCounter+4]=normal->getX()*normalY;
			normalArray[posCounter+5]=normal->getZ();
			normalArray[posCounter+6]=normal->getX()*normalX;
			normalArray[posCounter+7]=normal->getX()*normalY;
			normalArray[posCounter+8]=normal->getZ();
			posCounter = posCounter + 9;

			delete normal;


		}
	}

	setTexture();

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

	setTexture();

	program->setTexture(3);
	program->setActualProgram();

	glBindBuffer( GL_ARRAY_BUFFER, bufferNormalHandler);
	glVertexAttribPointer( VERTEX_NOR_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferColorHandler);
	glVertexAttribPointer( VERTEX_COL_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferPositionHandler);
	glVertexAttribPointer( VERTEX_POS_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferTextureHandler);
	glBufferData( GL_ARRAY_BUFFER, (trianglesEstimated * 6) * sizeof (float), this->textureArray, GL_STATIC_DRAW );
	glVertexAttribPointer( VERTEX_TEX_ATTR_INDEX, 2 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glDrawArrays( GL_TRIANGLES, 0, trianglesEstimated * 3);

}

AssemblyLine::~AssemblyLine(){

}

