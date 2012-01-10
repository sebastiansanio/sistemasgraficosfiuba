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

class Camera {
public:
	Camera();
	void setPosition();
	void upz();
	void downz();
	void left();
	void right();
	virtual ~Camera();

private:
	float eye[3];
	float at[3];
	float up[3];
	float ratio;
	float anglehor;
	float anglevert;

	void calcPosition();
};

#endif /* CAMERA_H_ */
