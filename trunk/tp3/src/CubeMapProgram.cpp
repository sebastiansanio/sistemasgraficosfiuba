/*
 * CubeMapProgram.cpp
 *
 *  Created on: 28/01/2012
 *      Author: damian
 */

#include "CubeMapProgram.h"

CubeMapProgram* CubeMapProgram::instance = 0;// Inicializar el puntero
CubeMapProgram* CubeMapProgram::Instance ()
{
  if (instance == 0)  // ¿Es la primera llamada?
  {
    instance = new CubeMapProgram; // Creamos la instancia
  }
  return instance; // Retornamos la dirección de la instancia
}

CubeMapProgram::CubeMapProgram() {
	program = new MainProgram();

	program->addVertexShader("cubemap.vert");

	program->addFragmentShader("cubemap.frag");

	positionAttrib = program->AddAttribute(0,9,"VertexPosition");//new  Attribute(0, "VertexPosition", program->programHandler);

	colorAttrib = program->AddAttribute(1,9,"VertexColor");

	normalAttrib = program->AddAttribute(2,9,"VertexNormal");

	textureAttrib = program->AddAttribute(3,6,"TextureCoord");

	glActiveTexture(GL_TEXTURE15);
	GLuint tid;
	glGenTextures(1, &tid);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tid);

	BitMap* bitmap2 = new BitMap("piso.bmp");

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, bitmap2->getAncho(), bitmap2->getAlto(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap2->getMatriz());

	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, bitmap2->getAncho(), bitmap2->getAlto(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap2->getMatriz());

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, bitmap2->getAncho(), bitmap2->getAlto(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap2->getMatriz());

	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, bitmap2->getAncho(), bitmap2->getAlto(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap2->getMatriz());

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, bitmap2->getAncho(), bitmap2->getAlto(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap2->getMatriz());

	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, bitmap2->getAncho(), bitmap2->getAlto(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap2->getMatriz());

	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER,	GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER,	GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,	GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,	GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,	GL_CLAMP_TO_EDGE);

	this->actualTexId = 0;

	lights[0]= new Light(8.0,-5.0,10.0,8.0,-5.0,0.0);

	lights[1]= new Light(0.0,-5.0,10.0,-0.0,-5.0,0.0);

	lights[2]= new Light(-8.0,-5.0,10.0,-8.0,-5.0,0.0);

	lights[3]= new Light(8.0,5.0,10.0,8.0,5.0,0.0);

	lights[4]= new Light(0.0,5.0,10.0,0.0,5.0,0.0);

	lights[5]= new Light(-8.0,5.0,10.0,-8.0,5.0,0.0);

	setActualProgramFirstTime();

}

void CubeMapProgram::setTexture(int texId){
	this->actualTexId = texId;
}

void CubeMapProgram::updateBuffer(){
	positionAttrib->updateBuffer();
	colorAttrib->updateBuffer();
	normalAttrib->updateBuffer();
	textureAttrib->updateBuffer();
}

void CubeMapProgram::setPositionValue(int position, float value){
	positionAttrib->setValue(position,value);
}

void CubeMapProgram::setColorValue(int position, float value){
	colorAttrib->setValue(position,value);
}

void CubeMapProgram::setNormalValue(int position, float value){
	normalAttrib->setValue(position,value);
}

void CubeMapProgram::setTextureValue(int position, float value){
	textureAttrib->setValue(position,value);
}

void CubeMapProgram::setLightPosition(){

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

void CubeMapProgram::updateModelViewProjection(){
	GLfloat modelView[16];
	glGetFloatv (GL_MODELVIEW_MATRIX, modelView);

	program->setUniformMat4(modelView,"ModelViewMatrix");

	GLfloat projection[16];

	glGetFloatv(GL_PROJECTION_MATRIX, projection);

	program->setUniformMat4(projection,"ProjectionMatrix");

}

void CubeMapProgram::setActualProgramFirstTime(){
	program->linkProgramHandlerFirstTime();
	//Si se linkea el program handler se pierde la uniform así que hay que pasarla aca
	setLightPosition();
}

void CubeMapProgram::setActualProgram(){
	program->linkProgramHandler();
		//Si se linkea el program handler se pierde la uniform así que hay que pasarla aca
	setLightPosition();
}

void CubeMapProgram::drawTriangle(){
	this->updateBuffer();
	glDrawArrays( GL_TRIANGLES, 0, 3);
}

CubeMapProgram::~CubeMapProgram() {
	// TODO Auto-generated destructor stub
}

