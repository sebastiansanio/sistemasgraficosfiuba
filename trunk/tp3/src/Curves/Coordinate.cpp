#include "Coordinate.h"
#include "math.h"

Coordinate::Coordinate(float x,float y,float z){
	this->x=x;
	this->y=y;
	this->z=z;
}

float Coordinate::getX(){
	return x;

}

float Coordinate::getY(){
	return y;

}

float Coordinate::getZ(){
	return z;

}

void Coordinate::normalize(){
	float norm = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
	x = x/norm;
	y = y/norm;
	z = z/norm;

}


