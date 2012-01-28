/*
 * MainProgram.h
 *
 *  Created on: 09/01/2012
 *      Author: damian
 */

#ifndef MAINPROGRAM_H_
#define MAINPROGRAM_H_

#define NUMLIGHT 6

#include "Shader.h"
#include "Attribute.h"
#include <list>

class MainProgram {

public:
	MainProgram();
	bool linkProgramHandler();
	Attribute* AddAttribute(int index, int tamData, char* name);
	void addVertexShader(char* name);
	void addFragmentShader(char* name);
	void setUniformMat4(GLfloat* data, char* name);
	void setUniformVec3(GLfloat* data, char* name);
	void setUniformInt(GLint data, char* name);
	virtual ~MainProgram();

private:
	GLuint programHandler;
};

#endif /* MAINPROGRAM_H_ */
