#include "BSpline.h"

#include <iostream>
#define INCREMENTO 0.1

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

	for(int j=0;j<(size-2);j=j+2){
		for(float i=0;i <= 1.001;i+=INCREMENTO){
			auxX=((1/2)*(1-i)*(1-i))*controlPoints->at(j)->getX()+(-i*i+i+1/2)*controlPoints->at(j+1)->getX();
			auxX+=(i*i/2)*controlPoints->at(j+2)->getX();
			auxY=((1/2)*(1-i)*(1-i))*controlPoints->at(j)->getY()+(-i*i+i+1/2)*controlPoints->at(j+1)->getY();
			auxY+=(i*i/2)*controlPoints->at(j+2)->getY();
			auxZ=((1/2)*(1-i)*(1-i))*controlPoints->at(j)->getZ()+(-i*i+i+1/2)*controlPoints->at(j+1)->getZ();
			auxZ+=(i*i/2)*controlPoints->at(j+2)->getZ();
			Coordinate* curveCoordinate=new Coordinate(auxX,auxY,auxZ);
			curvePoints->push_back(curveCoordinate);
		}
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
