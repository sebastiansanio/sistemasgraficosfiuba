#include "suelo.h"

GLuint suelo::dlSuelo;

suelo::suelo(){

}

void suelo::inicializar(){

	dlSuelo=glGenLists(1);
	glNewList(dlSuelo,GL_COMPILE);
	glPushMatrix();
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.60f, 0.15f);
	glVertex3f(-200.0,-200.0,0.0);
	glVertex3f(-200.0,200.0,0.0);
	glVertex3f(200.0,200.0,0.0);
	glVertex3f(200.0,-200.0,0.0);
	glEnd();
	glPopMatrix();
	glEndList();
}


void suelo::dibujar(){
	glCallList(suelo::dlSuelo);
}
