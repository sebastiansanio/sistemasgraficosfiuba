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

	lights[0]= new Light(5.0,0.0,3.0,5.0,0.0,0.0);

	lights[1]= new Light(0.0,0.0,3.0,0.0,0.0,0.0);

	setActualProgram();

	lightPos[0] = 5.0;
	lightPos[1] = 0.0;
	lightPos[2] = 3.0;

	lightSpotDir[0] = 5.0;
	lightSpotDir[1] = 0.0;
	lightSpotDir[2] = 0.0;


}

void BasicProgram::updateBuffer(){
	positionAttrib->updateBuffer();
	colorAttrib->updateBuffer();
	normalAttrib->updateBuffer();
	//Esto no tiene que estar hardcodeado en el program
	//setLightPosition(0.0,0.0,1.0,"lightPos");
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

void BasicProgram::setLightPosition(){

	int pos=0;

	for(int i = 0; i < NUMLIGHT; i++){
		float* data = lights[i]->getLightPosViewCoord();
		arrayBuffer[pos++] = data[0];
		arrayBuffer[pos++] = data[1];
		arrayBuffer[pos++] = data[2];
	}

	program->setUniformVec3(arrayBuffer,"lightPos");

	pos=0;

	for(int i = 0; i < NUMLIGHT; i++){
		float* data = lights[i]->getLightSpotDirViewCoord();
		arrayBuffer[pos++] = data[0];
		arrayBuffer[pos++] = data[1];
		arrayBuffer[pos++] = data[2];
	}

	program->setUniformVec3(arrayBuffer,"lightSpotDir");

}

void BasicProgram::updateModelViewProjection(){
	GLfloat modelView[16];
	glGetFloatv (GL_MODELVIEW_MATRIX, modelView);

	program->setUniformMat4(modelView,"ModelViewMatrix");

	GLfloat projection[16];

	glGetFloatv(GL_PROJECTION_MATRIX, projection);

	program->setUniformMat4(projection,"ProjectionMatrix");

}

void BasicProgram::setActualProgram(){
	program->linkProgramHandler();
	//Si se linkea el program handler se pierde la uniform así que hay que pasarla aca
	setLightPosition();
}

void BasicProgram::drawTriangle(){
	this->updateBuffer();
	glDrawArrays( GL_TRIANGLES, 0, 3);
}

BasicProgram::~BasicProgram() {
	// TODO Auto-generated destructor stub
}
