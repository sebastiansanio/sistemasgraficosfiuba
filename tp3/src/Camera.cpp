/*
 * Camera.cpp
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#include "Camera.h"

Camera* Camera::instance = 0;// Inicializar el puntero
Camera* Camera::Instance ()
{
  if (instance == 0)  // ¿Es la primera llamada?
  {
    instance = new Camera(); // Creamos la instancia
  }
  return instance; // Retornamos la dirección de la instancia
}

Camera::Camera() {
	ratio=2.0f;
	anglehor=0.0f;
	anglevert= 3.1416 / 2;

	calcPosition();
}

void Camera::setPosition(){
	gluLookAt(eye[0],eye[1],eye[2],at[0],at[1],at[2],up[0],up[1],up[2]);
	glGetFloatv (GL_MODELVIEW_MATRIX, viewMatrix);
}

float* Camera::transformViewCoord(float x, float y, float z){
	cout << "Light:" << x << "; " << y << "; " << z << endl;
	cout << "Eye:" << eye[0] << "; " << eye[1] << "; " << eye[2] << endl;
	transf[0] = (viewMatrix[0] * x) + (viewMatrix[1] * y) + (viewMatrix[2] * z) + viewMatrix[3];
	transf[1] = (viewMatrix[4] * x) + (viewMatrix[5] * y) + (viewMatrix[6] * z) + viewMatrix[7];
	transf[2] = (viewMatrix[8] * x) + (viewMatrix[9] * y) + (viewMatrix[10] * z) + viewMatrix[11];
	cout << endl;
	cout << endl;
	cout << viewMatrix[0] << "	" << viewMatrix[1] << "	" << viewMatrix[2] << "	" << viewMatrix[3] << endl;
	cout << viewMatrix[4] << "	" << viewMatrix[5] << "	" << viewMatrix[6] << "	" << viewMatrix[7] << endl;
	cout << viewMatrix[8] << "	" << viewMatrix[9] << "	" << viewMatrix[10] << "	" << viewMatrix[11] << endl;
	cout << viewMatrix[12] << "	" << viewMatrix[13] << "	" << viewMatrix[14] << "	" << viewMatrix[15] << endl;
	cout << endl;
	cout << endl;
	return transf;
}

void Camera::upz(){
	anglevert+=0.05;
	if(anglevert > 3.14) anglevert = 3.14;
	calcPosition();
}
void Camera::downz(){
	anglevert-=0.05;
	if(anglevert < 0.05) anglevert = 0.05;
	calcPosition();
}
void Camera::left(){
	anglehor-=0.05;
	if(anglehor < 0) anglehor = (3.14 * 2);
	calcPosition();
}

void Camera::right(){
	anglehor+=0.05;
	if(anglehor > (3.14 * 2)) anglehor = 0;
	calcPosition();
}

void Camera::nearRatio(){
	ratio-=0.05;
	if(ratio < 0.05) ratio = 0.05;
	calcPosition();
}

void Camera::farRatio(){
	ratio+=0.05;
	calcPosition();
}

void Camera::calcPosition(){
	eye[0]= ratio * cos(anglehor) * sin(anglevert);
	eye[1]= ratio * sin(anglehor) * sin(anglevert);
	eye[2]= -ratio * cos(anglevert);

	at[0] = 0.0;
	at[1] = 0.0;
	at[2] = 0.0;

	up[0] = 0.0;
	up[1] = 0.0;
	up[2] = 1.0;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

