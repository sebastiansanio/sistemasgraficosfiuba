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
#include <math.h>
#include <iostream>
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
	void nearRatio();
	void farRatio();
	GLfloat inverseViewMatrix[16];
	float eye[3];
	virtual ~Camera();

protected:
	Camera();
	Camera(const Camera & ) ;
	Camera &operator= (const Camera & ) ;

private:
	static Camera* instance;
	float at[3];
	float up[3];
	float transf[3];
	float ratio;
	float anglehor;
	float anglevert;
	GLfloat viewMatrix[16];
	float** inverseTemp;
	float** matrixTemp;

	void calcPosition();

	void MatrixInversion(float **A, int order, float **Y);
	int GetMinor(float **src, float **dest, int row, int col, int order);
	double CalcDeterminant( float **mat, int order);
};

#endif /* CAMERA_H_ */
