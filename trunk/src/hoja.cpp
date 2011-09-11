#include "hoja.h"

GLuint hoja::dlHoja;

hoja::hoja(){

}

void hoja::inicializar(){

	dlHoja=glGenLists(1);
	glNewList(dlHoja,GL_COMPILE);

	glPushMatrix();
	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0, 0.8f, 0.2f);
	glVertex3f(0.05,0.05,0.0);
	glColor3f(0.0, 0.7f, 0.3f);
	glVertex3f(0.1,0.1,0.0);
	glColor3f(0.0, 0.75f, 0.25f);
	glVertex3f(0.15,0.05,0.0);
	glColor3f(0.0, 0.8f, 0.2f);
	glVertex3f(0.1,0.0,0.0);
	glColor3f(0.0, 0.7f, 0.3f);
	glVertex3f(0.05,0.025,0.0);
	glColor3f(0.0, 0.75f, 0.25f);
	glVertex3f(0.0,0.05,0.0);
	glColor3f(0.0, 0.8f, 0.2f);
	glVertex3f(0.05,0.025,0.0);
	glColor3f(0.0, 0.7f, 0.3f);
	glVertex3f(0.1,0.1,0.0);
	glEnd();

	glPopMatrix();
	glEndList();
}


void hoja::dibujar(){
	glCallList(hoja::dlHoja);
}
