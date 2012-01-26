/*
 * Attribute.cpp
 *
 *  Created on: 09/01/2012
 *      Author: damian
 */

#include "Attribute.h"

Attribute::Attribute(int index, char* attribName, int tamData, GLuint programHandler) {
	this->index = index;
	this->attribName = attribName;
	this->tamData = tamData;
	this->data = new float[this->tamData];

	for(int i = 0; i < this->tamData; i++){
		this->data[i] = 0.0f;
	}

	glGenBuffers(1, &bufferHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferHandler);
	//Suponiendo que todos los atributos son 3 vectores de dimension 3
	glBufferData( GL_ARRAY_BUFFER, this->tamData * sizeof (float), this->data, GL_STATIC_DRAW );
	glEnableVertexAttribArray(this->index);
	glBindBuffer( GL_ARRAY_BUFFER, bufferHandler);
	glVertexAttribPointer( this->index, (this->tamData) / 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindAttribLocation( programHandler, this->index, this->attribName );

}

void Attribute::setValue(int position, float value){
	this->data[position] = value;
}

void Attribute::updateBuffer(){
	glBindBuffer( GL_ARRAY_BUFFER, bufferHandler );
	glBufferData( GL_ARRAY_BUFFER, this->tamData * sizeof (float), data, GL_STATIC_DRAW );
	glEnableVertexAttribArray(index);
	glBindBuffer( GL_ARRAY_BUFFER, bufferHandler);
	glVertexAttribPointer( index, (this->tamData) / 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
}

Attribute::~Attribute() {
	delete [] this->data;
	this->data = NULL;
}

