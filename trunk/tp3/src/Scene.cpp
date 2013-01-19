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
	generateBottleTime = 0;
	generateBottleDelay = 100;
	this->piso = new RectangTex(10.0,10.0,0,2.0);
	this->pared = new RectangTex(10.0,5.0,1,2.0);
	this->techo = new RectangTex(10.0,10.0,2,2.0);
	this->cube1 = new CubeRef(1.0,1.0,1.0);
	this->rectang = new Rectang(1.0,1.0,0.5);
	this->lampara = new Lampara();
	this->bottle = new Bottle();

	assemblyLine = new AssemblyLine();
	assemblyLine->addBottle();
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
			glPushMatrix();
				glTranslatef(8.0,5.0,10.0);
				glPushMatrix();
					glRotatef(180,0.0,1.0,0.0);
					lampara->print();
				glPopMatrix();
				glTranslatef(-8.0,0.0,0.0);
				glPushMatrix();
					glRotatef(180,0.0,1.0,0.0);
					lampara->print();
				glPopMatrix();
				glTranslatef(-8.0,0.0,0.0);
				glPushMatrix();
					glRotatef(180,0.0,1.0,0.0);
					lampara->print();
				glPopMatrix();
				glTranslatef(0.0,-10.0,0.0);
				glPushMatrix();
					glRotatef(180,0.0,1.0,0.0);
					lampara->print();
				glPopMatrix();
				glTranslatef(8.0,0.0,0.0);
				glPushMatrix();
					glRotatef(180,0.0,1.0,0.0);
					lampara->print();
				glPopMatrix();
				glTranslatef(8.0,0.0,0.0);
				glPushMatrix();
					glRotatef(180,0.0,1.0,0.0);
					lampara->print();
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0,0.0,0.8);
				assemblyLine->print();
			glPopMatrix();


	glPopMatrix();
}

void Scene::advanceMotion(){
	if(generateBottleTime<=0){
		assemblyLine->addBottle();
		generateBottleTime += generateBottleDelay;
	}else{
		generateBottleTime --;
	}


	assemblyLine->advance(0.05);

}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

