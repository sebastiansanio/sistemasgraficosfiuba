/*
 * AssemblyLine.cpp
 *
 *  Created on: 16/01/2013
 *      Author: Sebastián
 */

#include "AssemblyLine.h"
#include "Bottle.h"
#include "BottleFiller.h"
#include "BottleLabeler.h"
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

void AssemblyLine::advance(){

	double speed = 0.05;

	bool continueWork = true;
	for(unsigned int i = 0;i<bottles->size();i++){
		if(bottles->at(i)->getDistance()>=labelerPosition && bottles->at(i)->getHasLabel()==false){
			bool finnished = BottleLabeler::Instance()->label(bottles->at(i));
			if(finnished == false)
				continueWork = false;
		}
		if(bottles->at(i)->isFilled() == false && bottles->at(i)->getDistance()>=fillerPosition){
			bool finnished = BottleFiller::Instance()->fill(bottles->at(i));
			if(finnished == false)
				continueWork = false;
		}

	}


	if(continueWork == false)
		return;

	if(advanceParameter>=2){
		addBottle();
		advanceParameter -= 2;
	}

	advanceParameter += speed;
	for(unsigned int i = 0;i<bottles->size();i++){
		bottles->at(i)->setDistance(bottles->at(i)->getDistance()+speed);
	}

	setTexture();
	glBindBuffer( GL_ARRAY_BUFFER, bufferTextureHandler);
	glBufferData( GL_ARRAY_BUFFER, (trianglesEstimated * 6) * sizeof (float), this->textureArray, GL_STATIC_DRAW );

}


void AssemblyLine::setTexture(){

	int texPosCounter = 0;

	double sectionLen = 1;
	double texFrom = 0.0;
	double texTo;

	for(unsigned int i = 0;i<size-1;i++){

		texTo = texFrom + (pointsDistance->at(i+1)-pointsDistance->at(i))*sectionLen;


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
			textureArray[texPosCounter]=texFrom-advanceParameter;
			textureArray[texPosCounter+3]=horizontalParameterTo;
			textureArray[texPosCounter+2]=texTo-advanceParameter;
			textureArray[texPosCounter+5]=horizontalParameterFrom;
			textureArray[texPosCounter+4]=texTo-advanceParameter;
			texPosCounter = texPosCounter+6;

			textureArray[texPosCounter+1]=horizontalParameterFrom;
			textureArray[texPosCounter]=texFrom-advanceParameter;
			textureArray[texPosCounter+3]=horizontalParameterTo;
			textureArray[texPosCounter+2]=texTo-advanceParameter;
			textureArray[texPosCounter+5]=horizontalParameterTo;
			textureArray[texPosCounter+4]=texFrom-advanceParameter;
			texPosCounter = texPosCounter+6;
		}
		texFrom = texTo;
	}

}

AssemblyLine::AssemblyLine(){
	fillerPosition = 20;
	labelerPosition = 26;
	advanceParameter = 0;
	bottles = new vector<BottleInstance*>;

	program = TextureProgram::Instance();

	BSpline* bspline = new BSpline();
	bspline->addPoint(-13,-6,0);
	bspline->addPoint(-10,-6,0);
	bspline->addPoint(-6,-5,0);
	bspline->addPoint(-6,5,0);
	bspline->addPoint(1,4,0);
	bspline->addPoint(10,4,0);
	bspline->addPoint(14,4,0);

	bspline->calculate();
	points= bspline->getPoints();
	size = points->size();

	vector<Coordinate*>* section = new vector<Coordinate*>;
	section->push_back(new Coordinate(-0.6,0,-0.79));
	section->push_back(new Coordinate(-0.6,0,0.2));
	section->push_back(new Coordinate(-0.5,0,0.2));
	section->push_back(new Coordinate(-0.5,0,0));
	section->push_back(new Coordinate(0.5,0,0));
	section->push_back(new Coordinate(0.5,0,0.2));
	section->push_back(new Coordinate(0.6,0,0.2));
	section->push_back(new Coordinate(0.6,0,-0.79));
	section->push_back(new Coordinate(-0.6,0,-0.79));
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
	calculateDistances();
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

void AssemblyLine::calculateDistances(){
	pointsDistance = new vector<double>;
	double distance = 0;
	pointsDistance->push_back(distance);
	for (unsigned int i=0;i<points->size()-1;i++){
		distance += sqrt(pow(points->at(i+1)->getX()-points->at(i)->getX(),2)+pow(points->at(i+1)->getY()-points->at(i)->getY(),2));
		pointsDistance->push_back(distance);
	}

}

void AssemblyLine::print(){


	program->setTexture(3);
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

	drawBottles();

}

void AssemblyLine::drawBottles(){

	for(unsigned int i = 0;i<bottles->size();i++){
		if(bottles->at(i)->getDistance() >= pointsDistance->at(pointsDistance->size()-1)){
			bottles->erase(bottles->begin()+i);
			continue;
		}
	}
	for(unsigned int i = 0;i<bottles->size();i++){
		for (unsigned int j = 0;j<pointsDistance->size()-1;j++){
			if(bottles->at(i)->getDistance() >= pointsDistance->at(j) && bottles->at(i)->getDistance() <  pointsDistance->at(j+1)){
				double proportion = (bottles->at(i)->getDistance()-pointsDistance->at(j))/(pointsDistance->at(j+1)-pointsDistance->at(j));
				double posX = points->at(j)->getX()*(1-proportion) + points->at(j+1)->getX() * (proportion);
				double posY = points->at(j)->getY()*(1-proportion) + points->at(j+1)->getY() * (proportion);
				double liquidHeight = bottles->at(i)->getLiquidHeight();
				bool hasLabel = bottles->at(i)->getHasLabel();
				glPushMatrix();
					glTranslatef(posX,posY,0);
					Bottle::Instance()->print(liquidHeight,hasLabel);
				glPopMatrix();
				break;
			}
		}
	}
}

void AssemblyLine::addBottle(){
	BottleInstance* bottle= new BottleInstance(0,0,false);
	bottles->push_back(bottle);
}

AssemblyLine::~AssemblyLine(){

}

