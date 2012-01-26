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

Attribute* MainProgram::AddAttribute(int index, int tamData, char* name){
	return new Attribute(index, name, tamData, this->programHandler);
}

void MainProgram::addVertexShader(char* name){
	new Shader(GL_VERTEX_SHADER,name, programHandler);
}

void MainProgram::addFragmentShader(char* name){
	new Shader(GL_FRAGMENT_SHADER,name, programHandler);
}

void MainProgram::setUniformMat4(GLfloat* data, char* name){
	GLuint location = glGetUniformLocation(programHandler, name);
	if( location >= 0 )
	{
		glUniformMatrix4fv(location, 1, GL_FALSE,data);
	}
}

void MainProgram::setUniformVec3(GLfloat* data, char* name){
	GLuint location = glGetUniformLocation(programHandler, name);
	if( location >= 0 )
	{
		glUniform3fv(location,NUMLIGHT,data);
	}
}

void MainProgram::setUniformInt(GLint data, char* name){
	GLuint location = glGetUniformLocation(programHandler, name);
	if( location >= 0 )
	{
		glUniform1i(location,data);
	}
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

