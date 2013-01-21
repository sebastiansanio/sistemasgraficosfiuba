#include "Bottle.h"
#define PI 3.14159265
#define STEP 10

Bottle* Bottle::instance = 0;
Bottle* Bottle::Instance ()
{
  if (instance == 0)
  {
    instance = new Bottle();
  }
  return instance;
}

Coordinate* Bottle::calculateNormal(vector<Coordinate*>* points,unsigned int i,float j){

	if(i==0){
		Coordinate* coordinate = new Coordinate(0,0,-1);
		return coordinate;
	}

	float prevY = points->at(i-1)->getY();
	float prevZ = points->at(i-1)->getZ();
	float actualY = points->at(i)->getY();
	float actualZ = points->at(i)->getZ();
	float deltaY = actualY - prevY;
	float deltaZ = actualZ - prevZ;
	float normalY = deltaZ;
	float normalZ = - deltaY;


	Coordinate* coordinate = new Coordinate(normalY*cos(PI*j/180),normalY*sin(PI*j/180),normalZ);
	coordinate->normalize();

	return coordinate;
}

double Bottle::getFilledHeight(){
	return filledHeight;
}

Bottle::Bottle(){

	filledHeight = 0.8;

	program = BottleProgram::Instance();
	bezier=new Bezier();

	bezier->addPoint(0,0,0);
	bezier->addPoint(0,0,0);
	bezier->addPoint(0,0,0);
	bezier->addPoint(0,1.5/10,0.01);

	bezier->addPoint(0,1.25/10,0.5/5);
	bezier->addPoint(0,1.25/10,0.75/5);
	bezier->addPoint(0,1.5/10,1.6/5);

	bezier->addPoint(0,1.5/10,1.75/5);
	bezier->addPoint(0,1.5/10,2.0/5);
	bezier->addPoint(0,1.5/10,3.0/5);

	bezier->addPoint(0,1.5/10,3.2/5);
	bezier->addPoint(0,0.5/10,4.0/5);
	bezier->addPoint(0,0.5/10,5.0/5);

	bezier->addPoint(0,0,5.0/5);
	bezier->addPoint(0,0,5.0/5);
	bezier->addPoint(0,0,5.0/5);

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
			Coordinate* normal = calculateNormal(points,i,j);
			normalArray[posCounter]=normal->getX();
			normalArray[posCounter+1]=normal->getY();
			normalArray[posCounter+2]=normal->getZ();
			delete normal;

			positionArray[posCounter+3]=points->at(i)->getY()*cos(PI*(j+STEP)/180);
			positionArray[posCounter+4]=points->at(i)->getY()*sin(PI*(j+STEP)/180);
			positionArray[posCounter+5]=points->at(i)->getZ();
			textureArray[texPosCounter+2]=(j+STEP)/labelXSize;
			textureArray[texPosCounter+3]=1-points->at(i)->getZ()/labelYSize;
			normal = calculateNormal(points,i,j+STEP);
			normalArray[posCounter+3]=normal->getX();
			normalArray[posCounter+4]=normal->getY();
			normalArray[posCounter+5]=normal->getZ();
			delete normal;

			positionArray[posCounter+6]=points->at(i+1)->getY()*cos(PI*j/180);
			positionArray[posCounter+7]=points->at(i+1)->getY()*sin(PI*j/180);
			positionArray[posCounter+8]=points->at(i+1)->getZ();
			textureArray[texPosCounter+4]=j/labelXSize;
			textureArray[texPosCounter+5]=1-points->at(i+1)->getZ()/labelYSize;
			normal = calculateNormal(points,i+1,j);
			normalArray[posCounter+6]=normal->getX();
			normalArray[posCounter+7]=normal->getY();
			normalArray[posCounter+8]=normal->getZ();
			delete normal;

			posCounter+=9;
			texPosCounter+=6;

			positionArray[posCounter]=points->at(i+1)->getY()*cos(PI*(j+STEP)/180);
			positionArray[posCounter+1]=points->at(i+1)->getY()*sin(PI*(j+STEP)/180);
			positionArray[posCounter+2]=points->at(i+1)->getZ();
			textureArray[texPosCounter]=(j+STEP)/labelXSize;
			textureArray[texPosCounter+1]=1-points->at(i+1)->getZ()/labelYSize;
			normal = calculateNormal(points,i+1,j+STEP);
			normalArray[posCounter]=normal->getX();
			normalArray[posCounter+1]=normal->getY();
			normalArray[posCounter+2]=normal->getZ();
			delete normal;

			positionArray[posCounter+3]=points->at(i)->getY()*cos(PI*(j+STEP)/180);
			positionArray[posCounter+4]=points->at(i)->getY()*sin(PI*(j+STEP)/180);
			positionArray[posCounter+5]=points->at(i)->getZ();
			textureArray[texPosCounter+2]=(j+STEP)/labelXSize;
			textureArray[texPosCounter+3]=1-points->at(i)->getZ()/labelYSize;
			normal = calculateNormal(points,i,j+STEP);
			normalArray[posCounter+3]=normal->getX();
			normalArray[posCounter+4]=normal->getY();
			normalArray[posCounter+5]=normal->getZ();
			delete normal;

			positionArray[posCounter+6]=points->at(i+1)->getY()*cos(PI*j/180);
			positionArray[posCounter+7]=points->at(i+1)->getY()*sin(PI*j/180);
			positionArray[posCounter+8]=points->at(i+1)->getZ();
			textureArray[texPosCounter+4]=j/labelXSize;
			textureArray[texPosCounter+5]=1-points->at(i+1)->getZ()/labelYSize;
			normal = calculateNormal(points,i+1,j);
			normalArray[posCounter+6]=normal->getX();
			normalArray[posCounter+7]=normal->getY();
			normalArray[posCounter+8]=normal->getZ();
			delete normal;

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

void Bottle::print(double liquidHeight,bool label){
	program->setTexture(14);
	program->setActualProgram();
	program->setLiquidHeight(liquidHeight,label);

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

void Bottle::printPack(){
	program->setTexture(14);
	program->setActualProgram();
	program->setLiquidHeight(filledHeight,true);
	glBindBuffer( GL_ARRAY_BUFFER, bufferNormalHandler);
	glVertexAttribPointer( VERTEX_NOR_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferColorHandler);
	glVertexAttribPointer( VERTEX_COL_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferPositionHandler);
	glVertexAttribPointer( VERTEX_POS_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferTextureHandler);
	glVertexAttribPointer( VERTEX_TEX_ATTR_INDEX, 2 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	double distance = 0.15;
	glPushMatrix();
		glTranslatef(distance,distance,0);
		glDrawArrays( GL_TRIANGLES, 0, trianglesEstimated * 3);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-distance,-distance,0);
		glDrawArrays( GL_TRIANGLES, 0, trianglesEstimated * 3);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(distance,-distance,0);
		glDrawArrays( GL_TRIANGLES, 0, trianglesEstimated * 3);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-distance,distance,0);
		glDrawArrays( GL_TRIANGLES, 0, trianglesEstimated * 3);
	glPopMatrix();


}

Bottle::~Bottle(){

}
