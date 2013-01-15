#include "BSpline.h"

#include <iostream>
#include "math.h"
#define BSSTEP 0.05

BSpline::BSpline(){
	controlPoints = new vector<Coordinate*>;
	curvePoints = new vector<Coordinate*>;

}

void BSpline::addPoint(float x,float y, float z){
	Coordinate* coordinate=new Coordinate(x,y,z);
	controlPoints->push_back(coordinate);

}

void BSpline::calculate(){
	float auxX;
	float auxY;
	float auxZ;

	int size=controlPoints->size();

	if(size<3)
		return;

	for(float i=1;i < size-1+0.001;i+=BSSTEP){

		int intPart = (int) i;
		float u= i - intPart;

		auxX=(1/2)*pow(u,2)*controlPoints->at(i)->getX()+(-pow(u,2)+u+(1/2))*controlPoints->at(i+1)->getX();
		auxX+=(1/2)*pow(1-u,2)*controlPoints->at(i+2)->getX();
		auxY=(1/2)*pow(u,2)*controlPoints->at(i)->getY()+(-pow(u,2)+u+(1/2))*controlPoints->at(i+1)->getY();
		auxY+=(1/2)*pow(1-u,2)*controlPoints->at(i+2)->getY();
		auxZ=(1/2)*pow(u,2)*controlPoints->at(i)->getZ()+(-pow(u,2)+u+(1/2))*controlPoints->at(i+1)->getZ();
		auxZ+=(1/2)*pow(1-u,2)*controlPoints->at(i+2)->getZ();
		Coordinate* curveCoordinate=new Coordinate(auxX,auxY,auxZ);
		curvePoints->push_back(curveCoordinate);
	}
}

bool BSpline::isEmpty(){
	return (curvePoints->size()==0);
}

vector<Coordinate*>* BSpline::getPoints(){
	return curvePoints;

}

Coordinate* BSpline::getPoint(){

	Coordinate* coordinate=curvePoints->front();
	Coordinate* coordinateNew=new Coordinate(coordinate->getX(),coordinate->getY(),coordinate->getZ());
	curvePoints->erase(curvePoints->begin());
	return coordinateNew;
}

void BSpline::eraseAll(){
	delete controlPoints;
	controlPoints = new vector<Coordinate*>;
}

BSpline::~BSpline(){
	delete controlPoints;
	delete curvePoints;
}
