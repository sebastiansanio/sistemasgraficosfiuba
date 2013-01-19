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
	double auxX;
	double auxY;
	double auxZ;

	int size=controlPoints->size();

	if(size<3)
		return;

	for(double i=1;i <= size-1;i+=BSSTEP){

		int intPart = (int) i;
		float u = i - intPart;

		auxX=0.5*pow(1-u,2)*controlPoints->at(i-1)->getX()+(-pow(u,2)+u+0.5)*controlPoints->at(i)->getX();
		auxX+=0.5*pow(u,2)*controlPoints->at(i+1)->getX();
		auxY=0.5*pow(1-u,2)*controlPoints->at(i-1)->getY()+(-pow(u,2)+u+0.5)*controlPoints->at(i)->getY();
		auxY+=0.5*pow(u,2)*controlPoints->at(i+1)->getY();
		auxZ=0.5*pow(1-u,2)*controlPoints->at(i-1)->getZ()+(-pow(u,2)+u+0.5)*controlPoints->at(i)->getZ();
		auxZ+=0.5*pow(u,2)*controlPoints->at(i+1)->getZ();
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
