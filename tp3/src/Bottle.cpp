#include "Bottle.h"
#define PI 3.14159265
#define STEP 20

Bottle::Bottle(){
	program = BottleProgram::Instance();
	bezier=new Bezier();
	bezier->addPoint(0,0,0);
	bezier->addPoint(0,0.25,0);
	bezier->addPoint(0,0.23,0.1);
	bezier->addPoint(0,0.22,0.8);
	bezier->addPoint(0,0.20,0.9);
	bezier->addPoint(0,0.03,1.1);
	bezier->addPoint(0,0.04,1.2);
	bezier->calculate();


	vector<Coordinate*>* points= bezier->getPoints();
	unsigned int size = points->size();

	float ySize = points->at(size-1)->getZ() - points->at(0)->getZ();
	float labelXSize = 180;
	float labelYSize = ySize;


	trianglesEstimated = 2*(points->size()-1)*360/STEP;

	this->positionArray = new float[trianglesEstimated*9];
	this->colorArray = new float[trianglesEstimated*9];
	this->normalArray = new float[trianglesEstimated*9];
	this->textureArray = new float[trianglesEstimated*6];


	int posCounter = 0;
	int texPosCounter = 0;

	for(unsigned int i=0;i<size-1;i++){
		for(float j=0;j<360;j=j+STEP){

			positionArray[posCounter]=points->at(i)->getY()*cos(PI*j/180);
			positionArray[posCounter+1]=points->at(i)->getY()*sin(PI*j/180);
			positionArray[posCounter+2]=points->at(i)->getZ();
			textureArray[texPosCounter]=j/labelXSize;
			textureArray[texPosCounter+1]=1-points->at(i)->getZ()/labelYSize;

			positionArray[posCounter+3]=points->at(i)->getY()*cos(PI*(j+STEP)/180);
			positionArray[posCounter+4]=points->at(i)->getY()*sin(PI*(j+STEP)/180);
			positionArray[posCounter+5]=points->at(i)->getZ();
			textureArray[texPosCounter+2]=(j+STEP)/labelXSize;
			textureArray[texPosCounter+3]=1-points->at(i)->getZ()/labelYSize;

			positionArray[posCounter+6]=points->at(i+1)->getY()*cos(PI*j/180);
			positionArray[posCounter+7]=points->at(i+1)->getY()*sin(PI*j/180);
			positionArray[posCounter+8]=points->at(i+1)->getZ();
			textureArray[texPosCounter+4]=j/labelXSize;
			textureArray[texPosCounter+5]=1-points->at(i+1)->getZ()/labelYSize;

			posCounter+=9;
			texPosCounter+=6;

			positionArray[posCounter]=points->at(i+1)->getY()*cos(PI*(j+STEP)/180);
			positionArray[posCounter+1]=points->at(i+1)->getY()*sin(PI*(j+STEP)/180);
			positionArray[posCounter+2]=points->at(i+1)->getZ();
			textureArray[texPosCounter]=(j+STEP)/labelXSize;
			textureArray[texPosCounter+1]=1-points->at(i+1)->getZ()/labelYSize;

			positionArray[posCounter+3]=points->at(i)->getY()*cos(PI*(j+STEP)/180);
			positionArray[posCounter+4]=points->at(i)->getY()*sin(PI*(j+STEP)/180);
			positionArray[posCounter+5]=points->at(i)->getZ();
			textureArray[texPosCounter+2]=(j+STEP)/labelXSize;
			textureArray[texPosCounter+3]=1-points->at(i)->getZ()/labelYSize;

			positionArray[posCounter+6]=points->at(i+1)->getY()*cos(PI*j/180);
			positionArray[posCounter+7]=points->at(i+1)->getY()*sin(PI*j/180);
			positionArray[posCounter+8]=points->at(i+1)->getZ();
			textureArray[texPosCounter+4]=j/labelXSize;
			textureArray[texPosCounter+5]=1-points->at(i+1)->getZ()/labelYSize;

			posCounter+=9;
			texPosCounter+=6;
		}


	}
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

void Bottle::print(){
	program->setTexture(2);
	program->setActualProgram();

	program->setLiquidHeight(0.5,true);
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

Bottle::~Bottle(){

}
