/*
 * MainProgram.h
 *
 *  Created on: 09/01/2012
 *      Author: damian
 */

#ifndef MAINPROGRAM_H_
#define MAINPROGRAM_H_

#define NUMLIGHT 6
#define VERTEX_POS_ATTR_INDEX 0
#define VERTEX_COL_ATTR_INDEX 1
#define VERTEX_NOR_ATTR_INDEX 2
#define VERTEX_TEX_ATTR_INDEX 3

#include "Shader.h"
#include <list>

class MainProgram {

public:
	MainProgram();
	bool linkProgramHandler();
	bool linkProgramHandlerFirstTime();
	void addVertexShader(char* name);
	void addFragmentShader(char* name);
	void addAttributeLocationShader(int index, char* name);
	void setUniformMat4(GLfloat* data, char* name);
	void setUniformVec3(GLfloat* data, char* name);
	void setUniformVec3One(GLfloat* data, char* name);
	void setUniformInt(GLint data, char* name);
	virtual ~MainProgram();

//private:
	GLuint programHandler;
};

#endif /* MAINPROGRAM_H_ */
