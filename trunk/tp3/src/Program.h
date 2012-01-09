/*
 * Program.h
 *
 *  Created on: 08/01/2012
 *      Author: damian
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "Shader.h"
#include "Attribute.h"
#include <list>

class Program {
public:
	Program();
	void setActualProgram();
	void updateBuffer();
	void setPositionValue(int position, float value);
	void setColorValue(int position, float value);
	void drawTriangle();
	virtual ~Program();


private:
	GLuint programHandler;
	//GLuint vertexArrayHandler;
	Attribute* positionAttrib;
	Attribute* colorAttrib;

	void linkProgramHandler();
	void createVertexArray();
};

#endif /* PROGRAM_H_ */
