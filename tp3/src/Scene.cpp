/*
 * Scene.cpp
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#include "Scene.h"

Scene* Scene::instance = 0;// Inicializar el puntero
Scene* Scene::Instance ()
{
  if (instance == 0)  // ¿Es la primera llamada?
  {
    instance = new Scene(); // Creamos la instancia
  }
  return instance; // Retornamos la dirección de la instancia
}

Scene::Scene() {
	this->cube1 = new Cube(10,10,0.2,0);
	this->cube2 = new Cube(2,2,1,1);
}

void Scene::printScene(){
	glPushMatrix();
		this->cube1->print();
		glTranslatef(1.0,1.0,2.0);
		this->cube2->print();
	glPopMatrix();
}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

