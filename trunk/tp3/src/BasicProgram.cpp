/*
 * Program.cpp
 *
 *  Created on: 08/01/2012
 *      Author: damian
 */

#include "BasicProgram.h"

BasicProgram* BasicProgram::instance = 0;// Inicializar el puntero
BasicProgram* BasicProgram::Instance ()
{
  if (instance == 0)  // ¿Es la primera llamada?
  {
    instance = new BasicProgram; // Creamos la instancia
  }
  return instance; // Retornamos la dirección de la instancia
}

BasicProgram::BasicProgram() {
	program = new MainProgram();

	program->addVertexShader("basic.vert");

	program->addFragmentShader("basic.frag");

	positionAttrib = program->AddAttribute(0,"VertexPosition");//new  Attribute(0, "VertexPosition", program->programHandler);

	colorAttrib = program->AddAttribute(1,"VertexColor");

	normalAttrib = program->AddAttribute(2,"VertexNormal");

	setActualProgram();

}

void BasicProgram::updateBuffer(){
	positionAttrib->updateBuffer();
	colorAttrib->updateBuffer();
	normalAttrib->updateBuffer();
}

void BasicProgram::setPositionValue(int position, float value){
	positionAttrib->setValue(position,value);
}

void BasicProgram::setColorValue(int position, float value){
	colorAttrib->setValue(position,value);
}

void BasicProgram::setNormalValue(int position, float value){
	normalAttrib->setValue(position,value);
}

void BasicProgram::setActualProgram(){
	program->linkProgramHandler();
}

void BasicProgram::drawTriangle(){
	this->updateBuffer();
	glDrawArrays( GL_TRIANGLES, 0, 3);
}

BasicProgram::~BasicProgram() {
	// TODO Auto-generated destructor stub
}
