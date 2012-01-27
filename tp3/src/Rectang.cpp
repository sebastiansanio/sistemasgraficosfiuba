/*
 * Rectangle.cpp
 *
 *  Created on: 27/01/2012
 *      Author: damian
 */

#include "Rectang.h"

Rectang::Rectang(float xSize, float ySize) {
	this->x = xSize;
	this->y = ySize;
	this->program = BasicProgram::Instance();
}

void Rectang::print(){
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
	program->setPositionValue(2,0.0);
	program->setPositionValue(6,-1.0);
	program->setPositionValue(7,-1.0);
	program->setPositionValue(8,0.0);
	program->setPositionValue(5,0.0);
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
		glScalef(this->x,this->y,1.0);
		program->updateModelViewProjection();
		program->setPositionValue(3,1.0);
		program->setPositionValue(4,-1.0);
		program->drawTriangle();
		program->setPositionValue(3,-1.0);
		program->setPositionValue(4,1.0);
		program->drawTriangle();
	glPopMatrix();
}

Rectang::~Rectang() {
	// TODO Auto-generated destructor stub
}

