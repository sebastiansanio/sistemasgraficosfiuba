/*
 * Observador.cpp
 *
 *  Created on: Jan 15, 2013
 *      Author: damian
 */

#include "Observador.h"

Observador::Observador() {

}

void Observador::upz(){
}
void Observador::downz(){
}
void Observador::left(){
}

void Observador::right(){
}

void Observador::forward(){
}

void Observador::backward(){
}

float* Observador::getEye() {
	return eye;
}

float* Observador::getAt() {
	return at;
}

float* Observador::getUp() {
	return up;
}

Observador::~Observador() {
	// TODO Auto-generated destructor stub
}

