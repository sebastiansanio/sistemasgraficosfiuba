/*
 * Shader.cpp
 *
 *  Created on: 09/01/2012
 *      Author: damian
 */

#include "Shader.h"

Shader::Shader(GLenum type, char* name, GLuint programHandler) {
	shader = glCreateShader (type);
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
}

Shader::~Shader() {
	// TODO Auto-generated destructor stub
}

