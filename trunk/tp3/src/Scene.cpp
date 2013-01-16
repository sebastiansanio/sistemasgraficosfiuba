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
  if (instance == 0)  // �Es la primera llamada?
  {
    instance = new Scene(); // Creamos la instancia
  }
  return instance; // Retornamos la direcci�n de la instancia
}

Scene::Scene() {
	this->piso = new RectangTex(10.0,10.0,0,2.0);
	this->pared = new RectangTex(10.0,5.0,1,2.0);
	this->techo = new RectangTex(10.0,10.0,2,2.0);
	this->cube1 = new CubeRef(1.0,1.0,1.0);
	this->rectang = new Rectang(1.0,1.0,0.5);
	this->bottle = new Bottle();
	this->assemblyLine = new AssemblyLine();
}

void Scene::printScene(){
	glPushMatrix();
			//Dibujando el escenario
			piso->print();
			glPushMatrix();
				glTranslatef(0.0,10.0,5.0);
				glRotatef(90,1.0,0.0,0.0);
				pared->print();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0,-10.0,5.0);
				glRotatef(-90,1.0,0.0,0.0);
				pared->print();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-10.0,0.0,5.0);
				glRotatef(90,0.0,1.0,0.0);
				glRotatef(90,0.0,0.0,1.0);
				pared->print();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(10.0,0.0,5.0);
				glRotatef(-90,0.0,1.0,0.0);
				glRotatef(90,0.0,0.0,1.0);
				pared->print();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0,0.0,10.0);
				glRotatef(180,0.0,1.0,0.0);
				techo->print();
			glPopMatrix();
			bottle->print();
			glPushMatrix();
				glTranslatef(0.0,3.0,0.0);
				bottle->print();
				glTranslatef(0.0,3.0,0.0);
				bottle->print();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0,-3.0,0.0);
				bottle->print();
				glTranslatef(0.0,-3.0,0.0);
				bottle->print();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(3.0,0.0,0.0);
				bottle->print();
				glTranslatef(3.0,0.0,0.0);
				bottle->print();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-3.0,0.0,0.0);
				bottle->print();
				glTranslatef(-3.0,0.0,0.0);
				bottle->print();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0,0.0,2.0);
				assemblyLine->print();
			glPopMatrix();

	glPopMatrix();
}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

