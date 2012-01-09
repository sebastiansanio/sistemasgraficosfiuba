/*
 * Attribute.cpp
 *
 *  Created on: 09/01/2012
 *      Author: damian
 */

#include "Attribute.h"

Attribute::Attribute(int index, char* attribName, GLuint programHandler) {
	this->index = index;
	this->attribName = attribName;

	this->data[0] = 0.0f;
	this->data[1] = 0.0f;
	this->data[2] = 0.0f;
	this->data[3] = 0.0f;
	this->data[4] = 0.0f;
	this->data[5] = 0.0f;
	this->data[6] = 0.0f;
	this->data[7] = 0.0f;
	this->data[8] = 0.0f;

	glGenBuffers(1, &bufferHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferHandler);
	//Suponiendo que todos los atributos son 3 vectores de dimension 3
	glBufferData( GL_ARRAY_BUFFER, 9 * sizeof (float), this->data, GL_STATIC_DRAW );
	glEnableVertexAttribArray(this->index);
	glBindBuffer( GL_ARRAY_BUFFER, bufferHandler);
	glVertexAttribPointer( this->index, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindAttribLocation( programHandler, this->index, this->attribName );

}

void Attribute::setValue(int position, float value){
	this->data[position] = value;
}

void Attribute::updateBuffer(){
	glBindBuffer( GL_ARRAY_BUFFER, bufferHandler );
	glBufferData( GL_ARRAY_BUFFER, 9 * sizeof (float), data, GL_STATIC_DRAW );
	glEnableVertexAttribArray(index);
	glBindBuffer( GL_ARRAY_BUFFER, bufferHandler);
	glVertexAttribPointer( index, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
}

Attribute::~Attribute() {
	// TODO Auto-generated destructor stub
}

