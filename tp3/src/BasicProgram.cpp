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
  if (instance == 0)  // �Es la primera llamada?
  {
    instance = new BasicProgram; // Creamos la instancia
  }
  return instance; // Retornamos la direcci�n de la instancia
}

BasicProgram::BasicProgram() {
	program = new MainProgram();

	program->addVertexShader("basic.vert");

	program->addFragmentShader("basic.frag");

	program->addAttributeLocationShader(VERTEX_POS_ATTR_INDEX,"VertexPosition");
	program->addAttributeLocationShader(VERTEX_COL_ATTR_INDEX,"VertexColor");
	program->addAttributeLocationShader(VERTEX_NOR_ATTR_INDEX,"VertexNormal");


	lights[0]= new Light(8.0,-5.0,6.0,8.0,-5.0,0.0);

	lights[1]= new Light(0.0,-5.0,6.0,-0.0,-5.0,0.0);

	lights[2]= new Light(-8.0,-5.0,6.0,-8.0,-5.0,0.0);

	lights[3]= new Light(8.0,5.0,6.0,8.0,5.0,0.0);

	lights[4]= new Light(0.0,5.0,6.0,0.0,5.0,0.0);

	lights[5]= new Light(-8.0,5.0,6.0,-8.0,5.0,0.0);

	setActualProgramFirstTime();

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

void BasicProgram::setActualProgramFirstTime(){
	program->linkProgramHandlerFirstTime();
	//Si se linkea el program handler se pierde la uniform as� que hay que pasarla aca
	setLightPosition();
}

void BasicProgram::setActualProgram(){
	program->linkProgramHandler();
	//Si se linkea el program handler se pierde la uniform as� que hay que pasarla aca
	setLightPosition();
}

BasicProgram::~BasicProgram() {
	// TODO Auto-generated destructor stub
}

