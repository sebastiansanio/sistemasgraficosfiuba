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
			glVertex3f(radio*cos(PI*j/180),radio*sin(PI*j/180),0.0);
			glVertex3f(radio2*cos(PI*j/180),radio2*sin(PI*j/180),tall);
			glVertex3f(radio*cos(PI*(j+incremento)/180),radio*sin(PI*(j+incremento)/180),0.0);

			glVertex3f(radio2*cos(PI*j/180),radio2*sin(PI*j/180),tall);
			glVertex3f(radio2*cos(PI*(j+incremento)/180),radio2*sin(PI*(j+incremento)/180),tall);
			glVertex3f(radio*cos(PI*(j+incremento)/180),radio*sin(PI*(j+incremento)/180),0.0);
		}
	glEnd();
	glEndList();
}

rama::rama(float alto,float radio,float alturaPadre,float rotacion1,float rotacion2){
	cantHijos=0;

	this->tall=alto;
	this->radio=radio;
	this->radio2=aleatorio::obtener(0.4,0.6)*this->radio;
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
	if(edad<60){
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
	if(edad<60){
		float aux=(float)edad;
		glScalef(1,1,aux/60);
	}

	glCallList(dlBorde);
	glCallList(dlTapa);
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
	glTranslatef(0.0,0.0,0.95*tall*aux/60);
	glTranslatef(0.0,-radio2*aux/60,0.0);
	glRotatef(90,0.0,0.0,1.0);
	if(edad<60){
		glScalef(aux/60,aux/60,aux/60);
	}
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
		float nuevoAlto=aleatorio::obtener(tall*0.2,tall*0.4);
		float nuevoRadio=aleatorio::obtener(radio*0.5,radio*0.6);
		float rot1=aleatorio::obtener(10,20);
		float rotProm=180/(cantHijos-1);
		float rotDelta=360/((cantHijos-1)*5);
		float rot2=aleatorio::obtener(rotProm-rotDelta,rotProm+rotDelta);
		subRamas[0]=new rama(nuevoAlto,nuevoRadio,tall,rot1,rot2);

		for(int i=1;i<(cantHijos);i++){
			nuevoAlto=aleatorio::obtener(tall*0.5,tall*0.6);
			nuevoRadio=aleatorio::obtener(radio*0.4,radio*0.6);
			float altRel=aleatorio::obtener(0.62*tall,0.9*tall);
			rot1=aleatorio::obtener(42,46);

			rotProm=i*360/(cantHijos-1)+180/(cantHijos-1);
			rotDelta=360/((cantHijos-1)*5);
			rot2=aleatorio::obtener(rotProm-rotDelta,rotProm+rotDelta);
			subRamas[i]=new rama(nuevoAlto,nuevoRadio,altRel,rot1,rot2);
		}
	}
	else{
		for(int i=0;i<cantHijos;i++){
			subRamas[i]->agregarRama();
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
