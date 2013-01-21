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
	this->piso = new RectangTex(20.0,20.0,0,2.0);
	this->pared = new RectangTex(20.0,5.0,1,2.0);
	this->techo = new RectangTex(20.0,20.0,2,2.0);
	this->cube1 = new CubeRef(1.0,1.0,1.0);
	this->rectang = new Rectang(1.0,1.0,0.5);
	this->lampara = new Lampara();
	this->bottle = new Bottle();
	bottleGenerator = new BottleGenerator();
	assemblyLine = new AssemblyLine();
	bottleDispatcher = new BottleDispatcher();
	bullet = new Bullet();
}

void Scene::printScene(){
	glPushMatrix();
			//Dibujando el escenario
			piso->print();
			glPushMatrix();
				glTranslatef(0.0,20.0,5.0);
				glRotatef(90,1.0,0.0,0.0);
				pared->print();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0,-20.0,5.0);
				glRotatef(-90,1.0,0.0,0.0);
				pared->print();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-20.0,0.0,5.0);
				glRotatef(90,0.0,1.0,0.0);
				glRotatef(90,0.0,0.0,1.0);
				pared->print();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(20.0,0.0,5.0);
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
				glTranslatef(-12.5,-6.815,0);
				bottleGenerator->print();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(13,5,0);
				glRotatef(180,0,0,1);
				bottleDispatcher->print();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0,0.0,0.8);
				assemblyLine->print();
			glPopMatrix();
			bottle->printPack();

	glPopMatrix();
}

void Scene::advanceMotion(){
	bullet->advanceMotion();
	assemblyLine->advance();
}

Scene::~Scene() {

}

