/*
 * Cube.cpp
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#include "Cube.h"

Cube::Cube(float xSize, float ySize, float zSize) {
	this->x = xSize;
	this->y = ySize;
	this->z = zSize;
	program = BasicProgram::Instance();
}

void Cube::print(){
	program->setActualProgram();
	program->setColorValue(0,0.0);
	program->setColorValue(1,1.0);
	program->setColorValue(2,0.0);
	program->setColorValue(3,0.0);
	program->setColorValue(4,1.0);
	program->setColorValue(5,0.0);
	program->setColorValue(6,0.0);
	program->setColorValue(7,1.0);
	program->setColorValue(8,0.0);
	program->setPositionValue(0,1.0);
	program->setPositionValue(1,1.0);
	program->setPositionValue(2,1.0);
	program->setPositionValue(6,-1.0);
	program->setPositionValue(7,-1.0);
	program->setPositionValue(8,1.0);
	program->setPositionValue(5,1.0);
	program->setNormalValue(0,0.0);
	program->setNormalValue(1,0.0);
	program->setNormalValue(2,1.0);
	program->setNormalValue(3,0.0);
	program->setNormalValue(4,0.0);
	program->setNormalValue(5,1.0);
	program->setNormalValue(6,0.0);
	program->setNormalValue(7,0.0);
	program->setNormalValue(8,1.0);
	glPushMatrix();
		glScalef(this->x,this->y,this->z);
		glPushMatrix();
			drawRectangule();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90.0,1.0,0.0,0.0);
			drawRectangule();
		glPopMatrix();
		glPushMatrix();
			glRotatef(180.0,1.0,0.0,0.0);
			drawRectangule();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90.0,-1.0,0.0,0.0);
			drawRectangule();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90.0,0.0,1.0,0.0);
			drawRectangule();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90.0,0.0,-1.0,0.0);
			drawRectangule();
		glPopMatrix();
	glPopMatrix();
}

void Cube::drawRectangule(){
	//Se suponen que estan seteados los valores de las demas variables
	program->updateModelViewProjection();
	program->setPositionValue(3,1.0);
	program->setPositionValue(4,-1.0);
	program->drawTriangle();
	program->setPositionValue(3,-1.0);
	program->setPositionValue(4,1.0);
	program->drawTriangle();
}

Cube::~Cube() {
	// TODO Auto-generated destructor stub
}

