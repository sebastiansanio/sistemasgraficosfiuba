/*
 * TextureProgram.cpp
 *
 *  Created on: 24/01/2012
 *      Author: damian
 */

#include "TextureProgram.h"

TextureProgram* TextureProgram::instance = 0;// Inicializar el puntero
TextureProgram* TextureProgram::Instance ()
{
  if (instance == 0)  // �Es la primera llamada?
  {
    instance = new TextureProgram; // Creamos la instancia
  }
  return instance; // Retornamos la direcci�n de la instancia
}

TextureProgram::TextureProgram() {
	program = new MainProgram();

	program->addVertexShader("texture.vert");

	program->addFragmentShader("texture.frag");

	program->addAttributeLocationShader(VERTEX_POS_ATTR_INDEX,"VertexPosition");
	program->addAttributeLocationShader(VERTEX_COL_ATTR_INDEX,"VertexColor");
	program->addAttributeLocationShader(VERTEX_NOR_ATTR_INDEX,"VertexNormal");
	program->addAttributeLocationShader(VERTEX_TEX_ATTR_INDEX,"TextureCoord");

	glActiveTexture(GL_TEXTURE0);
	GLuint tid;
	glGenTextures(1, &tid);
	glBindTexture(GL_TEXTURE_2D, tid);
	BitMap* bitmap1 = new BitMap("floor.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap1->getAncho(), bitmap1->getAlto(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap1->getMatriz());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE1);
	GLuint tid2;
	glGenTextures(1, &tid2);
	glBindTexture(GL_TEXTURE_2D, tid2);
	BitMap* bitmap2 = new BitMap("wall.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap2->getAncho(), bitmap2->getAlto(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap2->getMatriz());
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

void TextureProgram::setTexture(int texId){
	this->actualTexId = texId;
}

void TextureProgram::setLightPosition(){

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

void TextureProgram::updateModelViewProjection(){
	GLfloat modelView[16];
	glGetFloatv (GL_MODELVIEW_MATRIX, modelView);

	program->setUniformMat4(modelView,"ModelViewMatrix");

	GLfloat projection[16];

	glGetFloatv(GL_PROJECTION_MATRIX, projection);

	program->setUniformMat4(projection,"ProjectionMatrix");

}

void TextureProgram::setActualProgramFirstTime(){
	program->linkProgramHandlerFirstTime();
	//Si se linkea el program handler se pierde la uniform as� que hay que pasarla aca
	setLightPosition();
}

void TextureProgram::setActualProgram(){
	program->linkProgramHandler();
		//Si se linkea el program handler se pierde la uniform as� que hay que pasarla aca
	setLightPosition();
}

TextureProgram::~TextureProgram() {
	// TODO Auto-generated destructor stub
}
