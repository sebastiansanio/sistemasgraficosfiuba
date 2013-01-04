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

	if(size<4)
		return;

	for(int j=0;j<(size-3);j=j+3){
		for(float i=0;i <= 1.001;i+=INCREMENTO){
			auxX=(1-i)*(1-i)*(1-i)*controlPoints->at(j)->getX()+3*(1-i)*(1-i)*i*controlPoints->at(j+1)->getX();
			auxX+=3*(1-i)*i*i*controlPoints->at(j+2)->getX()+i*i*i*controlPoints->at(j+3)->getX();
			auxY=(1-i)*(1-i)*(1-i)*controlPoints->at(j)->getY()+3*(1-i)*(1-i)*i*controlPoints->at(j+1)->getY();
			auxY+=3*(1-i)*i*i*controlPoints->at(j+2)->getY()+i*i*i*controlPoints->at(j+3)->getY();
			auxZ=(1-i)*(1-i)*(1-i)*controlPoints->at(j)->getZ()+3*(1-i)*(1-i)*i*controlPoints->at(j+1)->getZ();
			auxZ+=3*(1-i)*i*i*controlPoints->at(j+2)->getZ()+i*i*i*controlPoints->at(j+3)->getZ();
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
