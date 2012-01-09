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
	Attribute(int index, char* attribName, GLuint programHandler);
	void updateBuffer();
	void setValue(int position, float value);
	virtual ~Attribute();

private:
	float data[9];
	int index;
	GLuint bufferHandler;
	char* attribName;
};

#endif /* ATTRIBUTE_H_ */
