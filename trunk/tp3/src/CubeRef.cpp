/*
 * Cube.cpp
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#include "CubeRef.h"

CubeRef::CubeRef(float xSize, float ySize, float zSize) {
	this->x = xSize;
	this->y = ySize;
	this->z = zSize;
	this->rectang = new RectangRef(1.0,1.0,2.0);
}

void CubeRef::print(){
	glPushMatrix();
		glScalef(this->x,this->y,this->z);
		glPushMatrix();
			glTranslatef(0.0,0.0,1.0);
			this->rectang->print();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90.0,1.0,0.0,0.0);
			glTranslatef(0.0,0.0,1.0);
			this->rectang->print();
		glPopMatrix();
		glPushMatrix();
			glRotatef(180.0,1.0,0.0,0.0);
			glTranslatef(0.0,0.0,1.0);
			this->rectang->print();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90.0,-1.0,0.0,0.0);
			glTranslatef(0.0,0.0,1.0);
			this->rectang->print();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90.0,0.0,1.0,0.0);
			glTranslatef(0.0,0.0,1.0);
			this->rectang->print();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90.0,0.0,-1.0,0.0);
			glTranslatef(0.0,0.0,1.0);
			this->rectang->print();
		glPopMatrix();
	glPopMatrix();
}

CubeRef::~CubeRef() {
	// TODO Auto-generated destructor stub
}

