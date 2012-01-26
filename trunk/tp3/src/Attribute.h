/*
 * Attribute.h
 *
 *  Created on: 09/01/2012
 *      Author: damian
 */

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Attribute {
public:
	Attribute(int index, char* attribName, int tamData, GLuint programHandler);
	void updateBuffer();
	void setValue(int position, float value);
	virtual ~Attribute();

private:
	int tamData;
	float* data;
	int index;
	GLuint bufferHandler;
	char* attribName;
};

#endif /* ATTRIBUTE_H_ */
