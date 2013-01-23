/*
 * Camera.h
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>
#include "ObservadorCentro.h"
#include "ObservadorCaminante.h"
using namespace std;

class Camera {
public:
	static Camera* Instance();
	void setPosition();
	float* transformViewCoord(float x, float y, float z);
	void invertViewMatrix();
	void upz();
	void downz();
	void left();
	void right();
	void forward();
	void backward();
	void rotate(float angleX, float angleY);
	void toCaminante();
	void toCentro();
	GLfloat inverseViewMatrix[16];
	Observador* observador;
	virtual ~Camera();

protected:
	Camera();
	Camera(const Camera & ) ;
	Camera &operator= (const Camera & ) ;

private:
	static Camera* instance;
	float transf[3];
	GLfloat viewMatrix[16];
	float** inverseTemp;
	float** matrixTemp;

	void calcPosition();

	void MatrixInversion(float **A, int order, float **Y);
	int GetMinor(float **src, float **dest, int row, int col, int order);
	double CalcDeterminant( float **mat, int order);
};

#endif /* CAMERA_H_ */
