/*
 * Program.cpp
 *
 *  Created on: 08/01/2012
 *      Author: damian
 */

#include "Program.h"

Program::Program() {
	this->programHandler = glCreateProgram();
	if ( 0 == programHandler )
	{
		cout << "Error creating program object" << endl;
	}

	new Shader(GL_VERTEX_SHADER,"basic.vert", programHandler);

	new Shader(GL_FRAGMENT_SHADER,"basic.frag", programHandler);

	//createVertexArray();

	positionAttrib = new  Attribute(0, "VertexPosition", programHandler);

	colorAttrib = new Attribute(1, "VertexColor", programHandler);

	this->linkProgramHandler();

}

void Program::updateBuffer(){
	positionAttrib->updateBuffer();
	colorAttrib->updateBuffer();
}

void Program::setPositionValue(int position, float value){
	positionAttrib->setValue(position,value);
}

void Program::setColorValue(int position, float value){
	colorAttrib->setValue(position,value);
}

void Program::setActualProgram(){
	linkProgramHandler();
}

void Program::drawTriangle(){
	this->updateBuffer();
	glDrawArrays( GL_TRIANGLES, 0, 3);
}

void Program::linkProgramHandler(){
	glLinkProgram( programHandler );

	GLint status;
	glGetProgramiv( programHandler, GL_LINK_STATUS, &status );
	if( GL_FALSE == status )
	{
		cout << "Failed to link shader program!\n" << endl;
		GLint logLen;
		glGetProgramiv(programHandler, GL_INFO_LOG_LENGTH, &logLen);
		if( logLen > 0 )
		{
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(programHandler, logLen, &written, log);
			cout << "Program log: \n%s" << endl;
			free(log);
		}
	}
	else
	{
		glUseProgram( programHandler );
	}
}

/*void Program::createVertexArray(){
	glGenVertexArrays( 1, &vertexArrayHandler );
	glBindVertexArray( vertexArrayHandler );
}*/

Program::~Program() {
	// TODO Auto-generated destructor stub
}
