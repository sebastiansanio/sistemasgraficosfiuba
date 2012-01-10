/*
 * Camera.cpp
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#include "Camera.h"

Camera::Camera() {
	ratio=5.0f;
	anglehor=0.0f;
	anglevert= 3.1416 / 4;

	calcPosition();
}

void Camera::setPosition(){
	gluLookAt(eye[0],eye[1],eye[2],at[0],at[1],at[2],up[0],up[1],up[2]);
}

void Camera::upz(){
	anglevert+=0.1;
	calcPosition();
}
void Camera::downz(){
	anglevert-=0.1;
	calcPosition();
}
void Camera::left(){
	anglehor-=0.1;
	calcPosition();
}

void Camera::right(){
	anglehor+=0.1;
	calcPosition();
}

void Camera::calcPosition(){
	eye[0]= ratio * cos(anglehor) * sin(anglevert);
	eye[1]= ratio * sin(anglehor) * sin(anglevert);
	eye[2]= ratio * cos(anglevert);

	at[0] = 0.0;
	at[1] = 0.0;
	at[2] = 0.0;

	up[0] = 0.0;
	up[1] = 0.0;
	up[2] = 1.0;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

