/*
 * ObservadorCaminante.cpp
 *
 *  Created on: Jan 15, 2013
 *      Author: damian
 */

#include "ObservadorCaminante.h"
#define PI 3.14159265

ObservadorCaminante::ObservadorCaminante() {
	anguloX=PI;
	anguloY=PI/2;

	eye[0]= 9.0;
	eye[1]= 0.0;
	eye[2]= 2.0;

	at[0]=eye[0] + (1 * cos(anguloX) * sin (anguloY));
	at[1]=eye[1] + (1 * sin(anguloX) * sin (anguloY));
	at[2] = eye[2] + (1 * cos(anguloY));

	up[0] = 0.0;
	up[1] = 0.0;
	up[2] = 1.0;
}

void ObservadorCaminante::upz(){
	eye[2] = eye[2] + 0.1;
	at[2] = eye[2] + (1 * cos(anguloY));
}
void ObservadorCaminante::downz(){
	eye[2] = eye[2] - 0.1;
	at[2] = eye[2] + (1 * cos(anguloY));
}
void ObservadorCaminante::left(){
	//Con el angulo se donde estoy mirando, si le sumo 90 grados se hacia donde me tengo que mover
	//No se mueve en z
	float desplazamiento[2];
	desplazamiento[0] = cos(anguloX+(PI/2));
	desplazamiento[1] = sin(anguloX+(PI/2));
	eye[0] += desplazamiento[0] * 0.2;
	eye[1] += desplazamiento[1] * 0.2;
	at[0] += desplazamiento[0] * 0.2;
	at[1] += desplazamiento[1] * 0.2;
}

void ObservadorCaminante::right(){
	//Con el angulo se donde estoy mirando, si le sumo 90 grados se hacia donde me tengo que mover
	//No se mueve en z
	float desplazamiento[2];
	desplazamiento[0] = cos(anguloX+(PI/2));
	desplazamiento[1] = sin(anguloX+(PI/2));
	eye[0] -= desplazamiento[0] * 0.2;
	eye[1] -= desplazamiento[1] * 0.2;
	at[0] -= desplazamiento[0] * 0.2;
	at[1] -= desplazamiento[1] * 0.2;
}

void ObservadorCaminante::forward(){
	float distancia[3];
	distancia[0] = at[0] - eye[0];
	distancia[1] = at[1] - eye[1];
	distancia[2] = at[2] - eye[2];
	eye[0] += distancia[0] * 0.3;
	eye[1] += distancia[1] * 0.3;
	eye[2] += distancia[2] * 0.3;
	at[0] += distancia[0] * 0.3;
	at[1] += distancia[1] * 0.3;
	at[2] += distancia[2] * 0.3;

}

void ObservadorCaminante::backward(){
	float distancia[3];
	distancia[0] = at[0] - eye[0];
	distancia[1] = at[1] - eye[1];
	distancia[2] = at[2] - eye[2];
	eye[0] -= distancia[0] * 0.3;
	eye[1] -= distancia[1] * 0.3;
	eye[2] -= distancia[2] * 0.3;
	at[0] -= distancia[0] * 0.3;
	at[1] -= distancia[1] * 0.3;
	at[2] -= distancia[2] * 0.3;
}

void ObservadorCaminante::rotate(float angleX, float angleY){
	anguloX-=(PI*angleX/180);
	anguloY+=(PI*angleY/180);
	if(anguloX >= 2*PI) anguloX -= 2*PI;
	if(anguloY >= 2*PI) anguloY -= 2*PI;
	at[0]=eye[0] + (1 * cos(anguloX) * sin (anguloY));
	at[1]=eye[1] + (1 * sin(anguloX) * sin (anguloY));
	at[2] = eye[2] + (1 * cos(anguloY));
}

ObservadorCaminante::~ObservadorCaminante() {
	// TODO Auto-generated destructor stub
}

