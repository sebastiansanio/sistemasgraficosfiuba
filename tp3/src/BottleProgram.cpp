/*
 * TextureProgram.cpp
 *
 *  Created on: 24/01/2012
 *      Author: damian
 */

#include "BottleProgram.h"

BottleProgram* BottleProgram::instance = 0;// Inicializar el puntero
BottleProgram* BottleProgram::Instance ()
{
  if (instance == 0)  // �Es la primera llamada?
  {
    instance = new BottleProgram; // Creamos la instancia
  }
  return instance; // Retornamos la direcci�n de la instancia
}

BottleProgram::BottleProgram() {
	program = new MainProgram();

	program->addVertexShader("bottle.vert");

	program->addFragmentShader("bottle.frag");

	positionAttrib = program->AddAttribute(0,9,"VertexPosition");//new  Attribute(0, "VertexPosition", program->programHandler);

	colorAttrib = program->AddAttribute(1,9,"VertexColor");

	normalAttrib = program->AddAttribute(2,9,"VertexNormal");

	textureAttrib = program->AddAttribute(3,6,"TextureCoord");


	glActiveTexture(GL_TEXTURE2);
	GLuint tid3;
	glGenTextures(1, &tid3);
	glBindTexture(GL_TEXTURE_2D, tid3);
	BitMap* bitmap3 = new BitMap("cocacola.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap3->getAncho(), bitmap3->getAlto(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap3->getMatriz());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



	this->actualTexId = 0;

	lights[0]= new Light(8.0,-5.0,10.0,8.0,-5.0,0.0);

	lights[1]= new Light(0.0,-5.0,10.0,-0.0,-5.0,0.0);

	lights[2]= new Light(-8.0,-5.0,10.0,-8.0,-5.0,0.0);

	lights[3]= new Light(8.0,5.0,10.0,8.0,5.0,0.0);

	lights[4]= new Light(0.0,5.0,10.0,0.0,5.0,0.0);

	lights[5]= new Light(-8.0,5.0,10.0,-8.0,5.0,0.0);

	setActualProgramFirstTime();

}


void BottleProgram::setTexture(int texId){
	this->actualTexId = texId;
}

void BottleProgram::updateBuffer(){
	positionAttrib->updateBuffer();
	colorAttrib->updateBuffer();
	normalAttrib->updateBuffer();
	textureAttrib->updateBuffer();
}

void BottleProgram::setPositionValue(int position, float value){
	positionAttrib->setValue(position,value);
}

void BottleProgram::setColorValue(int position, float value){
	colorAttrib->setValue(position,value);
}

void BottleProgram::setNormalValue(int position, float value){
	normalAttrib->setValue(position,value);
}

void BottleProgram::setTextureValue(int position, float value){
	textureAttrib->setValue(position,value);
}

void BottleProgram::setLightPosition(){

	int pos=0;

	for(int i = 0; i < NUMLIGHT; i++){
		float* data = lights[i]->getLightPosViewCoord();
		arrayBuffer[pos++] = data[0];
		arrayBuffer[pos++] = data[1];
		arrayBuffer[pos++] = data[2];
	}

	program->setUniformVec3(arrayBuffer,"lightPos");

	program->setUniformInt(this->actualTexId,"Texture1");

	pos=0;

	for(int i = 0; i < NUMLIGHT; i++){
		float* data = lights[i]->getLightSpotDirViewCoord();
		arrayBuffer[pos++] = data[0];
		arrayBuffer[pos++] = data[1];
		arrayBuffer[pos++] = data[2];
	}

	program->setUniformVec3(arrayBuffer,"lightSpotDir");

}

void BottleProgram::updateModelViewProjection(){
	GLfloat modelView[16];
	glGetFloatv (GL_MODELVIEW_MATRIX, modelView);

	program->setUniformMat4(modelView,"ModelViewMatrix");

	GLfloat projection[16];

	glGetFloatv(GL_PROJECTION_MATRIX, projection);

	program->setUniformMat4(projection,"ProjectionMatrix");

}

void BottleProgram::setActualProgramFirstTime(){
	program->linkProgramHandlerFirstTime();
	//Si se linkea el program handler se pierde la uniform as� que hay que pasarla aca
	setLightPosition();
}

void BottleProgram::setActualProgram(){
	program->linkProgramHandler();
		//Si se linkea el program handler se pierde la uniform as� que hay que pasarla aca
	setLightPosition();
}

void BottleProgram::drawTriangle(){
	this->updateBuffer();
	glDrawArrays( GL_TRIANGLES, 0, 3);
}

BottleProgram::~BottleProgram() {
	// TODO Auto-generated destructor stub
}
