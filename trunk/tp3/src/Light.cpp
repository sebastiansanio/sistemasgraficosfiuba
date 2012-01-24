/*
 * Light.cpp
 *
 *  Created on: 23/01/2012
 *      Author: damian
 */

#include "Light.h"

Light::Light(float xPos, float yPos, float zPos, float xDir, float yDir, float zDir) {
	lightPos[0] = xPos;
	lightPos[1] = yPos;
	lightPos[2] = zPos;
	lightSpotDir[0] = xDir;
	lightSpotDir[1] = yDir;
	lightSpotDir[2] = zDir;
}

void Light::setViewCoords(){
	float* data = Camera::Instance()->transformViewCoord(lightPos[0],lightPos[1],lightPos[2]);
	lightPosViewCoord[0] = data[0];
	lightPosViewCoord[1] = data[1];
	lightPosViewCoord[2] = data[2];

	data = Camera::Instance()->transformViewCoord(lightSpotDir[0],lightSpotDir[1],lightSpotDir[2]);
	lightSpotDirViewCoord[0] = data[0];
	lightSpotDirViewCoord[1] = data[1];
	lightSpotDirViewCoord[2] = data[2];
}

float* Light::getLightSpotDirViewCoord(){
	this->setViewCoords();
	return this->lightSpotDirViewCoord;
}

float* Light::getLightPosViewCoord(){
	this->setViewCoords();
	return this->lightPosViewCoord;
}

Light::~Light() {
	// TODO Auto-generated destructor stub
}

