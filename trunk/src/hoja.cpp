#include "hoja.h"

GLuint hoja::dlHoja;

hoja::hoja(){

}

void hoja::inicializar(){

	dlHoja=glGenLists(1);
	glNewList(dlHoja,GL_COMPILE);

	glPushMatrix();
	glScalef(0.5,0.5,0.5);
	glColor3f(0.0, 0.8f, 0.2f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.05,0.05,0.0);
	glVertex3f(0.1,0.1,0.0);
	glVertex3f(0.15,0.05,0.0);
	glVertex3f(0.1,0.0,0.0);
	glVertex3f(0.05,0.025,0.0);
	glVertex3f(0.0,0.05,0.0);
	glVertex3f(0.05,0.025,0.0);
	glVertex3f(0.1,0.1,0.0);
	glEnd();

	glPopMatrix();
	glEndList();
}


void hoja::dibujar(){
	glCallList(hoja::dlHoja);
}
