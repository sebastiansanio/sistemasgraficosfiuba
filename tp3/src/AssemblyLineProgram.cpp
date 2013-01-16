/*
 * BottleProgram.cpp
 *
 *      Author: sebastian
 */

#include "AssemblyLineProgram.h"

AssemblyLineProgram* AssemblyLineProgram::instance = 0;
AssemblyLineProgram* AssemblyLineProgram::Instance ()
{
  if (instance == 0)
  {
    instance = new AssemblyLineProgram;
  }
  return instance;
}

AssemblyLineProgram::AssemblyLineProgram() {
	program = new MainProgram();

	program->addVertexShader("texture.vert");

	program->addFragmentShader("texture.frag");

	program->addAttributeLocationShader(VERTEX_POS_ATTR_INDEX,"VertexPosition");
	program->addAttributeLocationShader(VERTEX_COL_ATTR_INDEX,"VertexColor");
	program->addAttributeLocationShader(VERTEX_NOR_ATTR_INDEX,"VertexNormal");
	program->addAttributeLocationShader(VERTEX_TEX_ATTR_INDEX,"TextureCoord");

//	glActiveTexture(GL_TEXTURE14);
//	GLuint tid3;
//	glGenTextures(1, &tid3);
//	glBindTexture(GL_TEXTURE_2D, tid3);
//	BitMap* bitmap3 = new BitMap("cocacola.bmp");
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap3->getAncho(), bitmap3->getAlto(), 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap3->getMatriz());
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	this->actualTexId = 0;

	lights[0]= new Light(8.0,-5.0,10.0,8.0,-5.0,0.0);

	lights[1]= new Light(0.0,-5.0,10.0,-0.0,-5.0,0.0);

	lights[2]= new Light(-8.0,-5.0,10.0,-8.0,-5.0,0.0);

	lights[3]= new Light(8.0,5.0,10.0,8.0,5.0,0.0);

	lights[4]= new Light(0.0,5.0,10.0,0.0,5.0,0.0);

	lights[5]= new Light(-8.0,5.0,10.0,-8.0,5.0,0.0);

	setActualProgramFirstTime();

}


void AssemblyLineProgram::setTexture(int texId){
	this->actualTexId = texId;
}

void AssemblyLineProgram::setLightPosition(){

	int pos=0;

	for(int i = 0; i < NUMLIGHT; i++){
		float* data = lights[i]->getLightPosViewCoord();
		arrayBuffer[pos++] = data[0];
		arrayBuffer[pos++] = data[1];
		arrayBuffer[pos++] = data[2];
	}

	program->setUniformVec3(arrayBuffer,"lightPosition");

	program->setUniformInt(this->actualTexId,"Texture1");

	pos=0;

	for(int i = 0; i < NUMLIGHT; i++){
		float* data = lights[i]->getLightSpotDirViewCoord();
		arrayBuffer2[pos++] = data[0];
		arrayBuffer2[pos++] = data[1];
		arrayBuffer2[pos++] = data[2];
	}

	program->setUniformVec3(arrayBuffer2,"lightSpotDirect");

}

void AssemblyLineProgram::updateModelViewProjection(){
	GLfloat modelView[16];
	glGetFloatv (GL_MODELVIEW_MATRIX, modelView);

	program->setUniformMat4(modelView,"ModelViewMatrix");

	GLfloat projection[16];

	glGetFloatv(GL_PROJECTION_MATRIX, projection);

	program->setUniformMat4(projection,"ProjectionMatrix");

}

void AssemblyLineProgram::setActualProgramFirstTime(){
	program->linkProgramHandlerFirstTime();
	//Si se linkea el program handler se pierde la uniform as� que hay que pasarla aca
	setLightPosition();
}

void AssemblyLineProgram::setActualProgram(){
	program->linkProgramHandler();
		//Si se linkea el program handler se pierde la uniform as� que hay que pasarla aca
	setLightPosition();
}

