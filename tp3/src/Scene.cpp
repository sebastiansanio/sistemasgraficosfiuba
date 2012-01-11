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
	this->cube = new Cube(0.5,0.5,0.5);
}

void Scene::printScene(){
	this->cube->print();
}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

