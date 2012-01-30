/*
 * Rectangle.cpp
 *
 *  Created on: 27/01/2012
 *      Author: damian
 */

#include "Rectang.h"

Rectang::Rectang(float xSize, float ySize,float tamPaso) {
	this->x = xSize;
	this->y = ySize;
	this->tamPaso = tamPaso;
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
	program->setNormalValue(0,0.0);
	program->setNormalValue(1,0.0);
	program->setNormalValue(2,1.0);
	program->setNormalValue(3,0.0);
	program->setNormalValue(4,0.0);
	program->setNormalValue(5,1.0);
	program->setNormalValue(6,0.0);
	program->setNormalValue(7,0.0);
	program->setNormalValue(8,1.0);
	//program->updateModelViewProjection();
	for(float i = -(this->x); i < (this->x); i+=tamPaso){
		for(float j = -(this->y); j < (this->y); j+=tamPaso){
			//1
			program->setPositionValue(0,i);
			program->setPositionValue(1,j);
			program->setPositionValue(2,0.0);
			//2
			program->setPositionValue(6,i+tamPaso);
			program->setPositionValue(7,j+tamPaso);
			program->setPositionValue(8,0.0);
			//3
			program->setPositionValue(3,i+tamPaso);
			program->setPositionValue(4,j);
			program->setPositionValue(5,0.0);

			program->drawTriangle();

			//4
			program->setPositionValue(3,i);
			program->setPositionValue(4,j+tamPaso);
			program->setPositionValue(5,0.0);

			program->drawTriangle();
		}
	}
}

Rectang::~Rectang() {
	// TODO Auto-generated destructor stub
}

