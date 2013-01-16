/*
 * Generic.cpp
 *
 *  Created on: Jan 16, 2013
 *      Author: damian
 */

#include "Generic.h"

Generic::Generic(int cantTriangulos, float* positionArray, float* colorArray, float* normalArray) {
	this->cantTriangulos = cantTriangulos;
	this->positionArray = positionArray;
	this->colorArray = colorArray;
	this->normalArray = normalArray;

	this->program = BasicProgram::Instance();

	glGenBuffers(1, &bufferPositionHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferPositionHandler);
	glBufferData( GL_ARRAY_BUFFER, (this->cantTriangulos * 9) * sizeof (float), this->positionArray, GL_STATIC_DRAW );

	glGenBuffers(1, &bufferColorHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferColorHandler);
	glBufferData( GL_ARRAY_BUFFER, (this->cantTriangulos * 9) * sizeof (float), this->colorArray, GL_STATIC_DRAW );

	glGenBuffers(1, &bufferNormalHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferNormalHandler);
	glBufferData( GL_ARRAY_BUFFER, (this->cantTriangulos * 9) * sizeof (float), this->normalArray, GL_STATIC_DRAW );
}

void Generic::print(){
	program->setActualProgram();

	glBindBuffer( GL_ARRAY_BUFFER, bufferNormalHandler);
	glVertexAttribPointer( VERTEX_NOR_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferColorHandler);
	glVertexAttribPointer( VERTEX_COL_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferPositionHandler);
	glVertexAttribPointer( VERTEX_POS_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glDrawArrays( GL_TRIANGLES, 0, cantTriangulos * 3);
}

Generic::~Generic() {
	// TODO Auto-generated destructor stub
}

