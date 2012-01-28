/*
 * RectangTex.cpp
 *
 *  Created on: 27/01/2012
 *      Author: damian
 */

#include "RectangTex.h"

RectangTex::RectangTex(float xSize, float ySize, int texId,float tamTex) {
	// TODO Auto-generated constructor stub
	this->x = xSize;
	this->y = ySize;
	this->texId = texId;
	this->tamTex = tamTex;
	this->program = TextureProgram::Instance();
}

void RectangTex::print(){
	program->setTexture(this->texId);
	program->setActualProgram();
	program->setNormalValue(0,0.0);
	program->setNormalValue(1,0.0);
	program->setNormalValue(2,1.0);
	program->setNormalValue(3,0.0);
	program->setNormalValue(4,0.0);
	program->setNormalValue(5,1.0);
	program->setNormalValue(6,0.0);
	program->setNormalValue(7,0.0);
	program->setNormalValue(8,1.0);
	program->updateModelViewProjection();
	for(float i = -(this->x); i < (this->x); i+=tamTex){
		for(float j = -(this->y); j < (this->y); j+=tamTex){
			//1
			program->setPositionValue(0,i);
			program->setPositionValue(1,j);
			program->setPositionValue(2,0.0);
			program->setTextureValue(0,0.0);
			program->setTextureValue(1,0.0);
			//2
			program->setPositionValue(6,i+tamTex);
			program->setPositionValue(7,j+tamTex);
			program->setPositionValue(8,0.0);
			program->setTextureValue(4,1.0);
			program->setTextureValue(5,1.0);
			//3
			program->setPositionValue(3,i+tamTex);
			program->setPositionValue(4,j);
			program->setPositionValue(5,0.0);
			program->setTextureValue(2,1.0);
			program->setTextureValue(3,0.0);

			program->drawTriangle();

			//4
			program->setPositionValue(3,i);
			program->setPositionValue(4,j+tamTex);
			program->setPositionValue(5,0.0);
			program->setTextureValue(2,0.0);
			program->setTextureValue(3,1.0);

			program->drawTriangle();
		}
	}
}

RectangTex::~RectangTex() {
	// TODO Auto-generated destructor stub
}

