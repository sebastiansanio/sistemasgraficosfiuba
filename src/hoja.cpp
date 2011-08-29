#include "hoja.h"

GLuint hoja::dlHoja;

hoja::hoja(){

}

void hoja::inicializar(){

	dlHoja=glGenLists(1);
	glNewList(dlHoja,GL_COMPILE);
	glPushMatrix();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0, 0.8f, 0.2f);
	glVertex3f(0.1,0.1,0.0);
	glVertex3f(0.2,0.2,0.0);
	glVertex3f(0.3,0.1,0.0);
	glVertex3f(0.2,0.0,0.0);
	glVertex3f(0.1,0.05,0.0);
	glVertex3f(0.0,0.1,0.0);
	glVertex3f(0.1,0.15,0.0);
	glVertex3f(0.2,0.2,0.0);
	glEnd();

	glPopMatrix();
	glEndList();
}


void hoja::dibujar(){
	glCallList(hoja::dlHoja);
}
