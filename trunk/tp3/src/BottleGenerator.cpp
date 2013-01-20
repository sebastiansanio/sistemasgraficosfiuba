#include "BottleGenerator.h"
#include "Curves/Coordinate.h"

BottleGenerator* BottleGenerator::instance = 0;
BottleGenerator* BottleGenerator::Instance ()
{
  if (instance == 0)
  {
    instance = new BottleGenerator();
  }
  return instance;
}




BottleGenerator::BottleGenerator(){

	double height = 2.5;
	double width = 2;
	double length = 3;

	double entranceHeightFromFloor = 0.7;
	double entranceHeight = 1.2;
	double entranceWidth = 1.2;

	double entranceWidthLocation = (width-entranceWidth)/2;

	program = TextureProgram::Instance();
	trianglesEstimated = 18;

	this->positionArray = new float[trianglesEstimated*9];
	this->colorArray = new float[trianglesEstimated*9];
	this->normalArray = new float[trianglesEstimated*9];
	this->textureArray = new float[trianglesEstimated*6];

	int posCounter = 0;
	int texPosCounter = 0;

	//Floor
	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=0;
	normalArray[posCounter]=0;
	normalArray[posCounter+1]=0;
	normalArray[posCounter+2]=-1;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=0;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1;
	normalArray[posCounter+3]=0;
	normalArray[posCounter+4]=0;
	normalArray[posCounter+5]=-1;

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=0;
	textureArray[texPosCounter+4]=1;
	textureArray[texPosCounter+5]=0;
	normalArray[posCounter+6]=0;
	normalArray[posCounter+7]=0;
	normalArray[posCounter+8]=-1;
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=0;
	normalArray[posCounter]=0;
	normalArray[posCounter+1]=0;
	normalArray[posCounter+2]=-1;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=0;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1;
	normalArray[posCounter+3]=0;
	normalArray[posCounter+4]=0;
	normalArray[posCounter+5]=-1;

	positionArray[posCounter+6]=0;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=0;
	textureArray[texPosCounter+4]=0;
	textureArray[texPosCounter+5]=1;
	normalArray[posCounter+6]=0;
	normalArray[posCounter+7]=0;
	normalArray[posCounter+8]=-1;
	posCounter+=9;
	texPosCounter+=6;


	//Roof
	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=height;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=0;
	normalArray[posCounter]=0;
	normalArray[posCounter+1]=0;
	normalArray[posCounter+2]=1;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1;
	normalArray[posCounter+3]=0;
	normalArray[posCounter+4]=0;
	normalArray[posCounter+5]=1;

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=0;
	textureArray[texPosCounter+5]=1;
	normalArray[posCounter+6]=0;
	normalArray[posCounter+7]=0;
	normalArray[posCounter+8]=1;
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=height;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=0;
	normalArray[posCounter]=0;
	normalArray[posCounter+1]=0;
	normalArray[posCounter+2]=1;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1;
	normalArray[posCounter+3]=0;
	normalArray[posCounter+4]=0;
	normalArray[posCounter+5]=1;

	positionArray[posCounter+6]=0;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=1;
	textureArray[texPosCounter+5]=0;
	normalArray[posCounter+6]=0;
	normalArray[posCounter+7]=0;
	normalArray[posCounter+8]=1;
	posCounter+=9;
	texPosCounter+=6;

	//Back
	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=1-0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=0;
	normalArray[posCounter+1]=-1;
	normalArray[posCounter+2]=0;

	positionArray[posCounter+3]=0;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=0;
	textureArray[texPosCounter+2]=1-1;
	textureArray[texPosCounter+3]=1-0;
	normalArray[posCounter+3]=0;
	normalArray[posCounter+4]=-1;
	normalArray[posCounter+5]=0;

	positionArray[posCounter+6]=0;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=1-1;
	textureArray[texPosCounter+5]=1-1;
	normalArray[posCounter+6]=0;
	normalArray[posCounter+7]=-1;
	normalArray[posCounter+8]=0;
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=1-0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=0;
	normalArray[posCounter+1]=-1;
	normalArray[posCounter+2]=0;

	positionArray[posCounter+3]=0;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1-1;
	textureArray[texPosCounter+3]=1-1;
	normalArray[posCounter+3]=0;
	normalArray[posCounter+4]=-1;
	normalArray[posCounter+5]=0;

	positionArray[posCounter+6]=0;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=1-0;
	textureArray[texPosCounter+5]=1-1;
	normalArray[posCounter+6]=0;
	normalArray[posCounter+7]=-1;
	normalArray[posCounter+8]=0;
	posCounter+=9;
	texPosCounter+=6;


	//Lateral
	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=-1;
	normalArray[posCounter+1]=0;
	normalArray[posCounter+2]=0;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=0;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-1;
	normalArray[posCounter+3]=-1;
	normalArray[posCounter+4]=0;
	normalArray[posCounter+5]=0;

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=0;
	textureArray[texPosCounter+4]=1;
	textureArray[texPosCounter+5]=1-0;
	normalArray[posCounter+6]=-1;
	normalArray[posCounter+7]=0;
	normalArray[posCounter+8]=0;
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=0;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=-1;
	normalArray[posCounter+1]=0;
	normalArray[posCounter+2]=0;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=0;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-1;
	normalArray[posCounter+3]=-1;
	normalArray[posCounter+4]=0;
	normalArray[posCounter+5]=0;

	positionArray[posCounter+6]=0;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=0;
	textureArray[texPosCounter+5]=1-1;
	normalArray[posCounter+6]=-1;
	normalArray[posCounter+7]=0;
	normalArray[posCounter+8]=0;
	posCounter+=9;
	texPosCounter+=6;

	//Other lateral
	positionArray[posCounter]=0;
	positionArray[posCounter+1]=width;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=1-0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=1;
	normalArray[posCounter+1]=0;
	normalArray[posCounter+2]=0;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1-1;
	textureArray[texPosCounter+3]=1-1;
	normalArray[posCounter+3]=1;
	normalArray[posCounter+4]=0;
	normalArray[posCounter+5]=0;

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=0;
	textureArray[texPosCounter+4]=1-1;
	textureArray[texPosCounter+5]=1-0;
	normalArray[posCounter+6]=1;
	normalArray[posCounter+7]=0;
	normalArray[posCounter+8]=0;
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=0;
	positionArray[posCounter+1]=width;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=1-0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=1;
	normalArray[posCounter+1]=0;
	normalArray[posCounter+2]=0;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1-1;
	textureArray[texPosCounter+3]=1-1;
	normalArray[posCounter+3]=1;
	normalArray[posCounter+4]=0;
	normalArray[posCounter+5]=0;

	positionArray[posCounter+6]=0;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=1-0;
	textureArray[texPosCounter+5]=1-1;
	normalArray[posCounter+6]=1;
	normalArray[posCounter+7]=0;
	normalArray[posCounter+8]=0;
	posCounter+=9;
	texPosCounter+=6;

	//Front down
	positionArray[posCounter]=length;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=0;
	normalArray[posCounter+1]=1;
	normalArray[posCounter+2]=0;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=0;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-0;
	normalArray[posCounter+3]=0;
	normalArray[posCounter+4]=1;
	normalArray[posCounter+5]=0;

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=entranceHeightFromFloor;
	textureArray[texPosCounter+4]=1;
	textureArray[texPosCounter+5]=1-entranceHeightFromFloor/height;
	normalArray[posCounter+6]=0;
	normalArray[posCounter+7]=1;
	normalArray[posCounter+8]=0;
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=length;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=0;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-0;
	normalArray[posCounter]=0;
	normalArray[posCounter+1]=1;
	normalArray[posCounter+2]=0;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=entranceHeightFromFloor;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-entranceHeightFromFloor/height;
	normalArray[posCounter+3]=0;
	normalArray[posCounter+4]=1;
	normalArray[posCounter+5]=0;

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=entranceHeightFromFloor;
	textureArray[texPosCounter+4]=0;
	textureArray[texPosCounter+5]=1-entranceHeightFromFloor/height;
	normalArray[posCounter+6]=0;
	normalArray[posCounter+7]=1;
	normalArray[posCounter+8]=0;
	posCounter+=9;
	texPosCounter+=6;



	//Front up
	positionArray[posCounter]=length;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter]=0;
	normalArray[posCounter+1]=1;
	normalArray[posCounter+2]=0;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter+3]=0;
	normalArray[posCounter+4]=1;
	normalArray[posCounter+5]=0;

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=1;
	textureArray[texPosCounter+5]=1-1;
	normalArray[posCounter+6]=0;
	normalArray[posCounter+7]=1;
	normalArray[posCounter+8]=0;
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=length;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter]=0;
	normalArray[posCounter+1]=1;
	normalArray[posCounter+2]=0;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=height;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-1;
	normalArray[posCounter+3]=0;
	normalArray[posCounter+4]=1;
	normalArray[posCounter+5]=0;

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=height;
	textureArray[texPosCounter+4]=0;
	textureArray[texPosCounter+5]=1-1;
	normalArray[posCounter+6]=0;
	normalArray[posCounter+7]=1;
	normalArray[posCounter+8]=0;
	posCounter+=9;
	texPosCounter+=6;

	//Front medium left
	positionArray[posCounter]=length;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=entranceHeightFromFloor;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-entranceHeightFromFloor/height;
	normalArray[posCounter]=0;
	normalArray[posCounter+1]=1;
	normalArray[posCounter+2]=0;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=entranceWidthLocation;
	positionArray[posCounter+5]=entranceHeightFromFloor;
	textureArray[texPosCounter+2]=entranceWidthLocation/width;
	textureArray[texPosCounter+3]=1-entranceHeightFromFloor/height;
	normalArray[posCounter+3]=0;
	normalArray[posCounter+4]=1;
	normalArray[posCounter+5]=0;

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=entranceWidthLocation;
	positionArray[posCounter+8]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter+4]=entranceWidthLocation/width;
	textureArray[texPosCounter+5]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter+6]=0;
	normalArray[posCounter+7]=1;
	normalArray[posCounter+8]=0;
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=length;
	positionArray[posCounter+1]=0;
	positionArray[posCounter+2]=entranceHeightFromFloor;
	textureArray[texPosCounter]=0;
	textureArray[texPosCounter+1]=1-entranceHeightFromFloor/height;
	normalArray[posCounter]=0;
	normalArray[posCounter+1]=1;
	normalArray[posCounter+2]=0;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=entranceWidthLocation;
	positionArray[posCounter+5]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter+2]=entranceWidthLocation/width;
	textureArray[texPosCounter+3]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter+3]=0;
	normalArray[posCounter+4]=1;
	normalArray[posCounter+5]=0;

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=0;
	positionArray[posCounter+8]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter+4]=0;
	textureArray[texPosCounter+5]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter+6]=0;
	normalArray[posCounter+7]=1;
	normalArray[posCounter+8]=0;
	posCounter+=9;
	texPosCounter+=6;

	//Front medium right
	positionArray[posCounter]=length;
	positionArray[posCounter+1]=entranceWidthLocation+entranceWidth;
	positionArray[posCounter+2]=entranceHeightFromFloor;
	textureArray[texPosCounter]=(entranceWidthLocation+entranceWidth)/width;
	textureArray[texPosCounter+1]=1-entranceHeightFromFloor/height;
	normalArray[posCounter]=0;
	normalArray[posCounter+1]=1;
	normalArray[posCounter+2]=0;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=entranceHeightFromFloor;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-entranceHeightFromFloor/height;
	normalArray[posCounter+3]=0;
	normalArray[posCounter+4]=1;
	normalArray[posCounter+5]=0;

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=width;
	positionArray[posCounter+8]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter+4]=1;
	textureArray[texPosCounter+5]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter+6]=0;
	normalArray[posCounter+7]=1;
	normalArray[posCounter+8]=0;
	posCounter+=9;
	texPosCounter+=6;

	positionArray[posCounter]=length;
	positionArray[posCounter+1]=entranceWidthLocation+entranceWidth;
	positionArray[posCounter+2]=entranceHeightFromFloor;
	textureArray[texPosCounter]=(entranceWidthLocation+entranceWidth)/width;
	textureArray[texPosCounter+1]=1-entranceHeightFromFloor/height;
	normalArray[posCounter]=0;
	normalArray[posCounter+1]=1;
	normalArray[posCounter+2]=0;

	positionArray[posCounter+3]=length;
	positionArray[posCounter+4]=width;
	positionArray[posCounter+5]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter+2]=1;
	textureArray[texPosCounter+3]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter+3]=0;
	normalArray[posCounter+4]=1;
	normalArray[posCounter+5]=0;

	positionArray[posCounter+6]=length;
	positionArray[posCounter+7]=entranceWidthLocation+entranceWidth;
	positionArray[posCounter+8]=entranceHeightFromFloor+entranceHeight;
	textureArray[texPosCounter+4]=(entranceWidthLocation+entranceWidth)/width;
	textureArray[texPosCounter+5]=1-(entranceHeightFromFloor+entranceHeight)/height;
	normalArray[posCounter+6]=0;
	normalArray[posCounter+7]=1;
	normalArray[posCounter+8]=0;
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

void BottleGenerator::print(){
	program->setTexture(4);
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

BottleGenerator::~BottleGenerator(){

}
