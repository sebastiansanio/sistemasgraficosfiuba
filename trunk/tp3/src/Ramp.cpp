#include "Ramp.h"
#include "Curves/Coordinate.h"

Ramp* Ramp::instance = 0;
Ramp* Ramp::Instance ()
{
  if (instance == 0)
  {
    instance = new Ramp(4,2,5);
  }
  return instance;
}


Ramp::Ramp(double height,double width,double length){

	program = TextureProgram::Instance();
	trianglesEstimated = 2;

	this->positionArray = new float[trianglesEstimated*9];
	this->colorArray = new float[trianglesEstimated*9];
	this->normalArray = new float[trianglesEstimated*9];
	this->textureArray = new float[trianglesEstimated*6];

	int posCounter = 0;
	int texPosCounter = 0;

	double deltaZ=height;
	double deltaX=-length;

	double normalZ=-deltaX;
	double normalX=deltaZ;


	Coordinate* normal = new Coordinate(normalX,0,normalZ);
	normal->normalize();

	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=height;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-1;
	normalArray[posCounter]=normal->getX();
	normalArray[posCounter+1]=normal->getY();
	normalArray[posCounter+2]=normal->getZ();

	positionArray[posCounter+3]=0;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-1;
	normalArray[posCounter+3]=normal->getX();
	normalArray[posCounter+4]=normal->getY();
	normalArray[posCounter+5]=normal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=0;
	textureArray[texPosCounter+4]=1;
	textureArray[texPosCounter+5]=1-0;
	normalArray[posCounter+6]=normal->getX();
	normalArray[posCounter+7]=normal->getY();
	normalArray[posCounter+8]=normal->getZ();
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=height;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-1;
	normalArray[posCounter]=normal->getX();
	normalArray[posCounter+1]=normal->getY();
	normalArray[posCounter+2]=normal->getZ();

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=0;
	positionArray[posCounter+5]=0;
	textureArray[texPosCounter+2]=0;
	textureArray[texPosCounter+3]=1-0;
	normalArray[posCounter+3]=normal->getX();
	normalArray[posCounter+4]=normal->getY();
	normalArray[posCounter+5]=normal->getZ();

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=0;
	textureArray[texPosCounter+4]=1;
	textureArray[texPosCounter+5]=1-0;
	normalArray[posCounter+6]=normal->getX();
	normalArray[posCounter+7]=normal->getY();
	normalArray[posCounter+8]=normal->getZ();
	posCounter+=9;
	texPosCounter+=6;
	delete normal;


	glGenBuffers(1, &bufferPositionHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferPositionHandler);
	glBufferData( GL_ARRAY_BUFFER, (trianglesEstimated * 9) * sizeof (float), this->positionArray, GL_STATIC_DRAW );
	glGenBuffers(1, &bufferColorHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferColorHandler);
	glBufferData( GL_ARRAY_BUFFER, (trianglesEstimated * 9) * sizeof (float), this->colorArray, GL_STATIC_DRAW );
	glGenBuffers(1, &bufferNormalHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferNormalHandler);
	glBufferData( GL_ARRAY_BUFFER, (trianglesEstimated * 9) * sizeof (float), this->normalArray, GL_STATIC_DRAW );
	glGenBuffers(1, &bufferTextureHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferTextureHandler);
	glBufferData( GL_ARRAY_BUFFER, (trianglesEstimated * 6) * sizeof (float), this->textureArray, GL_STATIC_DRAW );

}

void Ramp::print(){
	program->setTexture(2);
	program->setActualProgram();

	glBindBuffer( GL_ARRAY_BUFFER, bufferNormalHandler);
	glVertexAttribPointer( VERTEX_NOR_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferColorHandler);
	glVertexAttribPointer( VERTEX_COL_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferPositionHandler);
	glVertexAttribPointer( VERTEX_POS_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferTextureHandler);
	glVertexAttribPointer( VERTEX_TEX_ATTR_INDEX, 2 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glDrawArrays( GL_TRIANGLES, 0, trianglesEstimated * 3);

}

Ramp::~Ramp(){

}
