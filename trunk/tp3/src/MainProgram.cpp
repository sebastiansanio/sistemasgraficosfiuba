/*
 * MainProgram.cpp
 *
 *  Created on: 09/01/2012
 *      Author: damian
 */

#include "MainProgram.h"

MainProgram::MainProgram() {
	this->programHandler = glCreateProgram();
	if ( 0 == programHandler )
	{
		cout << "Error creating program object" << endl;
	}
}

Attribute* MainProgram::AddAttribute(int index, char* name){
	return new Attribute(index, name, this->programHandler);
}

void MainProgram::addVertexShader(char* name){
	new Shader(GL_VERTEX_SHADER,name, programHandler);
}

void MainProgram::addFragmentShader(char* name){
	new Shader(GL_FRAGMENT_SHADER,name, programHandler);
}

void MainProgram::linkProgramHandler(){
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

MainProgram::~MainProgram() {
	// TODO Auto-generated destructor stub
}

