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

	program->addAttributeLocationShader(VERTEX_POS_ATTR_INDEX,"VertexPosition");
	program->addAttributeLocationShader(VERTEX_COL_ATTR_INDEX,"VertexColor");
	program->addAttributeLocationShader(VERTEX_NOR_ATTR_INDEX,"VertexNormal");
	program->addAttributeLocationShader(VERTEX_TEX_ATTR_INDEX,"TextureCoord");

	GLuint tex_cube = SOIL_load_OGL_cubemap
	(
		"xp1.png",
		"xn1.png",
		"yp1.png",
		"yn1.png",
		"zp1.png",
		"zn1.png",
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
	);

	glActiveTexture(GL_TEXTURE15);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex_cube);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER,	GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER,	GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,	GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,	GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,	GL_CLAMP_TO_EDGE);

	this->actualTexId = 15;

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

void CubeMapProgram::setLightPosition(){

	program->setUniformVec3One(Camera::Instance()->observador->getEye(),"camPos");

	int pos=0;

	for(int i = 0; i < NUMLIGHT; i++){
		float* data = lights[i]->getLightPosViewCoord();
		arrayBuffer[pos++] = data[0];
		arrayBuffer[pos++] = data[1];
		arrayBuffer[pos++] = data[2];
	}

	program->setUniformVec3(arrayBuffer,"lightPos");

	program->setUniformMat4(Camera::Instance()->inverseViewMatrix,"inverseMatrix");

	pos=0;

	for(int i = 0; i < NUMLIGHT; i++){
		float* data = lights[i]->getLightSpotDirViewCoord();
		arrayBuffer[pos++] = data[0];
		arrayBuffer[pos++] = data[1];
		arrayBuffer[pos++] = data[2];
	}

	program->setUniformVec3(arrayBuffer,"lightSpotDir");

	program->setUniformInt(this->actualTexId,"Texture2");

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

CubeMapProgram::~CubeMapProgram() {
	// TODO Auto-generated destructor stub
}

