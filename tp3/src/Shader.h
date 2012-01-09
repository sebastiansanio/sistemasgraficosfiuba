/*
 * Shader.h
 *
 *  Created on: 09/01/2012
 *      Author: damian
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Shader {
public:
	Shader(GLenum type, char* name, GLuint programHandler);
	virtual ~Shader();

private:
	GLuint shader;
};

#endif /* SHADER_H_ */
