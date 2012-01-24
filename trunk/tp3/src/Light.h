/*
 * Light.h
 *
 *  Created on: 23/01/2012
 *      Author: damian
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "Camera.h"

class Light {
public:
	Light(float xPos, float yPos, float zPos, float xDir, float yDir, float zDir);
	float* getLightPosViewCoord();
	float* getLightSpotDirViewCoord();
	virtual ~Light();

private:
	void setViewCoords();
	float lightPos[3];
	float lightSpotDir[3];
	float lightPosViewCoord[3];
	float lightSpotDirViewCoord[3];
};

#endif /* LIGHT_H_ */
