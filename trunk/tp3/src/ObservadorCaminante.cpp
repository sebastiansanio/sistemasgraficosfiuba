/*
 * ObservadorCaminante.cpp
 *
 *  Created on: Jan 15, 2013
 *      Author: damian
 */

#include "ObservadorCaminante.h"

ObservadorCaminante::ObservadorCaminante() {
	angulo=3.1416;

	eye[0]= 9.0;
	eye[1]= 0.0;
	eye[2]= 2.0;

	at[0]=eye[0] + (1 * cos(angulo));
	at[1]=eye[1] + (1 * sin(angulo));
	at[2] = eye[2];

	up[0] = 0.0;
	up[1] = 0.0;
	up[2] = 1.0;
}

void ObservadorCaminante::upz(){
	eye[2] = eye[2] + 0.05;
	at[2] = eye[2];
}
void ObservadorCaminante::downz(){
	eye[2] = eye[2] - 0.05;
	at[2] = eye[2];
}
void ObservadorCaminante::left(){
	angulo+=0.05;
	at[0]=eye[0] + (1 * cos(angulo));
	at[1]=eye[1] + (1 * sin(angulo));
}

void ObservadorCaminante::right(){
	angulo-=0.05;
	at[0]=eye[0] + (1 * cos(angulo));
	at[1]=eye[1] + (1 * sin(angulo));
}

void ObservadorCaminante::forward(){
	float distancia[3];
	distancia[0] = at[0] - eye[0];
	distancia[1] = at[1] - eye[1];
	distancia[2] = at[2] - eye[2];
	eye[0] += distancia[0] * 0.2;
	eye[1] += distancia[1] * 0.2;
	eye[2] += distancia[2] * 0.2;
	at[0] += distancia[0] * 0.2;
	at[1] += distancia[1] * 0.2;
	at[2] += distancia[2] * 0.2;

}

void ObservadorCaminante::backward(){
	float distancia[3];
	distancia[0] = at[0] - eye[0];
	distancia[1] = at[1] - eye[1];
	distancia[2] = at[2] - eye[2];
	eye[0] -= distancia[0] * 0.2;
	eye[1] -= distancia[1] * 0.2;
	eye[2] -= distancia[2] * 0.2;
	at[0] -= distancia[0] * 0.2;
	at[1] -= distancia[1] * 0.2;
	at[2] -= distancia[2] * 0.2;
}

ObservadorCaminante::~ObservadorCaminante() {
	// TODO Auto-generated destructor stub
}

