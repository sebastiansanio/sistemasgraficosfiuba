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
	this->piso = new RectangTex(10.0,10.0,0);
	this->pared = new RectangTex(10.0,10.0,1);
	this->cube1 = new CubeTex(4.0,4.0,2.0,1);
}

void Scene::printScene(){
	glPushMatrix();
		glPushMatrix();
			//Dibujando el escenario
			glScalef(1.0,1.0,0.5);
			piso->print();
			glPushMatrix();
				glTranslatef(0.0,10.0,10.0);
				glRotatef(90,1.0,0.0,0.0);
				pared->print();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0,-10.0,10.0);
				glRotatef(-90,1.0,0.0,0.0);
				pared->print();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-10.0,0.0,10.0);
				glRotatef(90,0.0,1.0,0.0);
				pared->print();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(10.0,0.0,10.0);
				glRotatef(-90,0.0,1.0,0.0);
				pared->print();
			glPopMatrix();
		glPopMatrix();
		glTranslatef(0.0,0.0,2.0);
		cube1->print();
	glPopMatrix();
}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

