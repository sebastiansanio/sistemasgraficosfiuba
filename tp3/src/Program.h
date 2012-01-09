/*
 * Program.h
 *
 *  Created on: 08/01/2012
 *      Author: damian
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

class Program {
public:
	Program();
	void setActualProgram();
	void updateBuffer();
	virtual ~Program();
	float positionData[9];
	float colorData[9];


private:
	GLuint programHandler;
	GLuint vertexArrayHandler;
	GLuint positionBufferHandler;
	GLuint colorBufferHandler;

	void linkProgramHandler();
	GLuint createShader(GLenum type, char* name);
	void createVertexArray();
	GLuint createAttribute(int index, float* data, char* attribName);
	void updateAttribBuffer(int index, float* data, GLuint handler);
};

#endif /* PROGRAM_H_ */
