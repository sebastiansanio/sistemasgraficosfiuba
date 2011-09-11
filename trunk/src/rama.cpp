#include "rama.h"
#include <math.h>


#define PI 3.14159265

void rama::tapa(){

	dlTapa = glGenLists(1);
	glNewList(dlTapa, GL_COMPILE);
	glColor3f(0.25, 0.19, 0.0);
	glBegin(GL_TRIANGLE_FAN);
		double incremento=360/(2^precision);

		glVertex3f(0.0,0.0,0.0);
		for(GLfloat j=0;j<=360;j=j+incremento)
		{
			glVertex3f(radio*cos(PI*j/180),radio*sin(PI*j/180),0.0);
		}
	glEnd();

	glPushMatrix();
	glTranslatef(0.0,0.0,tall);
	glBegin(GL_TRIANGLE_FAN);


		glVertex3f(0.0,0.0,0.0);
		for(GLfloat j=0;j<=360;j=j+incremento)
		{
			glVertex3f(radio2*cos(PI*j/180),radio2*sin(PI*j/180),0.0);
		}
	glEnd();
	glPopMatrix();
	glEndList();

}

void rama::borde(){

	dlBorde = glGenLists(1);
	glNewList(dlBorde,GL_COMPILE);
	glBegin(GL_TRIANGLES);
		double incremento=360/(2^precision);
		glShadeModel(GL_SMOOTH);
		glColor3f(0.25, 0.19, 0.0);
		for(GLfloat j=0;j<=360;j=j+incremento)
		{
			glColor3f(0.25, 0.19, 0.0);
			glVertex3f(radio*cos(PI*j/180),radio*sin(PI*j/180),0.0);
			glColor3f(0.30, 0.15, 0.0);
			glVertex3f(radio2*cos(PI*j/180),radio2*sin(PI*j/180),tall);
			glColor3f(0.27, 0.17, 0.0);
			glVertex3f(radio*cos(PI*(j+incremento)/180),radio*sin(PI*(j+incremento)/180),0.0);

			glColor3f(0.30, 0.15, 0.0);
			glVertex3f(radio2*cos(PI*j/180),radio2*sin(PI*j/180),tall);
			glColor3f(0.27, 0.17, 0.0);
			glVertex3f(radio2*cos(PI*(j+incremento)/180),radio2*sin(PI*(j+incremento)/180),tall);
			glColor3f(0.30, 0.15, 0.0);
			glVertex3f(radio*cos(PI*(j+incremento)/180),radio*sin(PI*(j+incremento)/180),0.0);
		}
	glEnd();
	glEndList();
}

rama::rama(float alto,float radio,float alturaPadre,float rotacion1,float rotacion2){
	cantHijos=0;

	this->tall=alto;
	this->radio=radio;
	this->radio2=aleatorio::obtener(0.6,0.7)*this->radio;
	this->rotacion1=rotacion1;
	this->rotacion2=rotacion2;
	this->alturaPadre=alturaPadre;
	this->edad=1;
	tapa();
	borde();

}

rama::~rama(){
	if(cantHijos!=0){
		for(int i=0;i<cantHijos;i++){
			delete subRamas[i];
		}
		cantHijos=0;
	}
}

void rama::crecer(){
	if(edad<75){
		edad++;
	}
	if(cantHijos!=0){
		for(int i=0;i<cantHijos;i++){
			subRamas[i]->crecer();;
		}
	}

}

void rama::dibujar(){
	glPushMatrix();
	if(edad<75){
		float aux=(float)edad;
		glScalef(aux/75,aux/75,aux/75);
	}

	glCallList(dlTapa);
	glCallList(dlBorde);
	glPopMatrix();

}

void rama::dibujarHijos(){

	if(cantHijos!=0){
		for(int i=0;i<cantHijos;i++){
			glPushMatrix();
			glTranslatef(0.0,0.0,subRamas[i]->alturaPadre);
			glRotatef(subRamas[i]->rotacion2,0.0,0.0,1.0);
			glRotatef(subRamas[i]->rotacion1,1.0,1.0,0.0);
			subRamas[i]->dibujar();
			subRamas[i]->dibujarHijos();
			glPopMatrix();
		}
	}
		float aux=(float) edad;
		glPushMatrix();
		glTranslatef(0.0,0.0,0.85*tall*aux/75);
		glTranslatef(radio2*aux/75,0.0,0.0);
		glRotatef(180,0.0,0.0,1.0);
		glScalef(aux/75,aux/75,aux/75);
		hoja::dibujar();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0,0.0,0.95*tall*aux/75);
		glTranslatef(0.0,-radio2*aux/75,0.0);
		glRotatef(90,0.0,0.0,1.0);
		glScalef(aux/75,aux/75,aux/75);
		hoja::dibujar();
		glPopMatrix();

}
int rama::getCantHijos(){
	return cantHijos;
}

void rama::agregarRama(){
	if(cantHijos==0){
		cantHijos=((int) aleatorio::obtener(4.0,6.4))+1;
		subRamas=new rama*[cantHijos];

		subRamas[0]=new rama(tall*0.3,radio2,tall,0,0);

		for(int i=1;i<cantHijos;i++){
			float nuevoAlto=aleatorio::obtener(tall*0.4,tall*0.5);
			float nuevoRadio=aleatorio::obtener(radio*0.3,radio*0.55);
			float altRel=aleatorio::obtener(0.7*tall,0.85*tall);
			float rot1=aleatorio::obtener(20,80); //20-65
			float rot2=aleatorio::obtener(i*360/(cantHijos-1),360/(cantHijos-1)+i*360/(cantHijos-1)); //0-360
			subRamas[i]=new rama(nuevoAlto,nuevoRadio,altRel,rot1,rot2);
		}
	}
	else{
		for(int i=0;i<cantHijos;i++){
			subRamas[i]->agregarRama();
		}
	}
}

void rama::quitarRama(){
	for(int i=0;i<cantHijos;i++){
		if(subRamas[i]->getCantHijos()==0){
			cantHijos=0;
			delete subRamas[i];
		}
		else{
			subRamas[i]->quitarRama();
		}
	}
}

float rama::getAlturaPadre(){
	return this->alturaPadre;
}
float rama::getRotacion1(){
	return this->rotacion1;
}
float rama::getRotacion2(){
	return this->rotacion2;
}
