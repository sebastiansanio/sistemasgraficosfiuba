#include "BottleFiller.h"
#include "Curves/Coordinate.h"
#include "Bottle.h"
#include "math.h"

BottleFiller* BottleFiller::instance = 0;
BottleFiller* BottleFiller::Instance ()
{
  if (instance == 0)
  {
    instance = new BottleFiller();
  }
  return instance;
}

bool BottleFiller::fill(BottleInstance* bottle){
	if(fillTime == 0){
		fillTime = 50;
		return false;
	}
	if(fillTime<=45 && fillTime>5){
		double actualLiquidHeight = bottle->getLiquidHeight();
		Bottle* paintBottle =  Bottle::Instance();
		double maxLiquidHeight = paintBottle->getFilledHeight();
		double fillRatio = maxLiquidHeight/40;
		double fill = min(fillRatio,maxLiquidHeight-actualLiquidHeight);
		bottle->setLiquidHeight(actualLiquidHeight+fill);
	}
	fillTime --;
	return fillTime == 0;
}

BottleFiller::BottleFiller(){


	fillTime = 0;
	program = TextureProgram::Instance();
	trianglesEstimated = 1;

	this->positionArray = new float[trianglesEstimated*9];
	this->colorArray = new float[trianglesEstimated*9];
	this->normalArray = new float[trianglesEstimated*9];
	this->textureArray = new float[trianglesEstimated*6];

	int posCounter = 0;
	int texPosCounter = 0;
	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=0;
	normalArray[posCounter]=0;
	normalArray[posCounter+1]=0;
	normalArray[posCounter+2]=1;

	positionArray[posCounter+3]=1;
	positionArray[posCounter+4]=1;
	positionArray[posCounter+5]=0;
	textureArray[texPosCounter+2]=0;
	textureArray[texPosCounter+3]=0;
	normalArray[posCounter+3]=0;
	normalArray[posCounter+4]=0;
	normalArray[posCounter+5]=1;

	positionArray[posCounter+6]=1;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=0;
	textureArray[texPosCounter+4]=0;
	textureArray[texPosCounter+5]=0;
	normalArray[posCounter+6]=0;
	normalArray[posCounter+7]=0;
	normalArray[posCounter+8]=1;
	posCounter+=9;
	texPosCounter+=6;


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

void BottleFiller::print(){
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

BottleFiller::~BottleFiller(){

}
