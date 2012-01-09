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

	createShader(GL_VERTEX_SHADER,"basic.vert");

	createShader(GL_FRAGMENT_SHADER,"basic.frag");

	this->positionData[0] = -0.8f;
	this->positionData[1] = -0.8f;
	this->positionData[2] = 0.0f;
	this->positionData[3] = 0.8f;
	this->positionData[4] = -0.8f;
	this->positionData[5] = 0.0f;
	this->positionData[6] = 0.0f;
	this->positionData[7] = 0.8f;
	this->positionData[8] = 0.0f;

	this->colorData[0] = 1.0f;
	this->colorData[1] = 1.0f;
	this->colorData[2] = 1.0f;
	this->colorData[3] = 0.0f;
	this->colorData[4] = 1.0f;
	this->colorData[5] = 0.0f;
	this->colorData[6] = 0.0f;
	this->colorData[7] = 0.0f;
	this->colorData[8] = 1.0f;

	createVertexArray();

	positionBufferHandler = createAttribute(0,positionData, "VertexPosition");

	colorBufferHandler = createAttribute(1,colorData, "VertexColor");

}

void Program::updateBuffer(){
	updateAttribBuffer(0,positionData,positionBufferHandler);
	updateAttribBuffer(1,colorData,colorBufferHandler);
}

void Program::updateAttribBuffer(int index, float* data, GLuint handler){
	glBindBuffer( GL_ARRAY_BUFFER, handler );
	glBufferData( GL_ARRAY_BUFFER, 9 * sizeof (float), data, GL_STATIC_DRAW );
	glEnableVertexAttribArray(index);
	glBindBuffer( GL_ARRAY_BUFFER, handler);
	glVertexAttribPointer( index, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
}

void Program::setActualProgram(){
	linkProgramHandler();
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

GLuint Program::createShader(GLenum type, char* name){
	GLuint shader = glCreateShader (type);
	if ( 0 == shader )
	{
		cout << "Error creating shader" << endl;
	}

	//Cargando el archivo en memoria
	ifstream v_shader_file(name, ifstream::in);
	string v_str((istreambuf_iterator<char>(v_shader_file)), istreambuf_iterator<char>());
	const char* vs_code_array[] = {v_str.c_str()};

	glShaderSource( shader, 1, vs_code_array, NULL);

	// Compilar el shader
	glCompileShader( shader );

	// verificar resultado de la compilacion
	GLint vs_compilation_result;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &vs_compilation_result );
	if( GL_FALSE == vs_compilation_result )
	{
		cout << "Vertex shader compilation failed!\n" << endl;
		GLint logLen;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLen );
		if( logLen > 0 )
		{
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, log);
			cout << "Shader log: " << log << endl;
			free(log);
		}
	}
	glAttachShader( programHandler, shader );

	linkProgramHandler();

	return shader;
}

void Program::createVertexArray(){
	glGenVertexArrays( 1, &vertexArrayHandler );
	glBindVertexArray( vertexArrayHandler );
}

GLuint Program::createAttribute(int index, float* data, char* attribName){
	GLuint attributeBufferHandle;
	glGenBuffers(1, &attributeBufferHandle);
	glBindBuffer( GL_ARRAY_BUFFER, attributeBufferHandle );
	glBufferData( GL_ARRAY_BUFFER, 9 * sizeof (float), data, GL_STATIC_DRAW );
	glEnableVertexAttribArray(index);
	glBindBuffer( GL_ARRAY_BUFFER, attributeBufferHandle);
	glVertexAttribPointer( index, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindAttribLocation( programHandler, index, attribName );

	linkProgramHandler();

	return attributeBufferHandle;
}

Program::~Program() {
	// TODO Auto-generated destructor stub
}
