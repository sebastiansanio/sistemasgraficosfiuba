/*
 * ObservadorCentro.cpp
 *
 *  Created on: Jan 15, 2013
 *      Author: damian
 */

#include "ObservadorCentro.h"

ObservadorCentro::ObservadorCentro() {
	ratio=10.0f;
	anglehor=0.0f;
	anglevert= 3.1416/2; //(3.1416 * 3) / 4;
	this->calcPosition();
}

void ObservadorCentro::upz(){
	anglevert+=0.02;
	if(anglevert > 3.14) anglevert = 3.14;
	calcPosition();
}
void ObservadorCentro::downz(){
	anglevert-=0.02;
	if(anglevert < 0.05) anglevert = 0.05;
	calcPosition();
}
void ObservadorCentro::left(){
	anglehor-=0.03;
	if(anglehor < 0) anglehor = (3.14 * 2);
	calcPosition();
}

void ObservadorCentro::right(){
	anglehor+=0.03;
	if(anglehor > (3.14 * 2)) anglehor = 0;
	calcPosition();
}

void ObservadorCentro::forward(){
	ratio-=0.05;
	if(ratio < 0.2) ratio = 0.2;
	calcPosition();
}

void ObservadorCentro::backward(){
	ratio+=0.05;
	calcPosition();
}

void ObservadorCentro::rotate(float angleX, float angleY){
}

void ObservadorCentro::calcPosition(){
	eye[0]= ratio * cos(anglehor) * sin(anglevert);
	eye[1]= ratio * sin(anglehor) * sin(anglevert);
	eye[2]= -ratio * cos(anglevert);

	at[0] = 0.0;
	at[1] = 0.0;
	at[2] = 2.0;

	up[0] = 0.0;
	up[1] = 0.0;
	up[2] = 1.0;
}

ObservadorCentro::~ObservadorCentro() {
	// TODO Auto-generated destructor stub
}

