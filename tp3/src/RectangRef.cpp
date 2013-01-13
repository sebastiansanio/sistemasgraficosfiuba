/*
 * RectangTex.cpp
 *
 *  Created on: 27/01/2012
 *      Author: damian
 */

#include "RectangRef.h"

RectangRef::RectangRef(float xSize, float ySize,double tamTex) {
	// TODO Auto-generated constructor stub
	this->x = xSize;
	this->y = ySize;
	this->texId = 15;
	this->tamTex = tamTex;
	this->program = CubeMapProgram::Instance();
	this->cantTriangulos = 0;

	int cantTriangulosEstimado = (xSize*2/tamTex)*(ySize*2/tamTex)*2;
	cantTriangulosEstimado = cantTriangulosEstimado * 2;

	this->positionArray = new float[cantTriangulosEstimado*9];
	this->colorArray = new float[cantTriangulosEstimado*9];
	this->normalArray = new float[cantTriangulosEstimado*9];
	this->textureArray = new float[cantTriangulosEstimado*6];

	int posCounter = 0;
	int texPosCounter = 0;

	for(float i = -(this->x); i < (this->x); i+=tamTex) {
			for(float j = -(this->y); j < (this->y); j+=tamTex){
				//Primer triangulo
				//Vertice 1
				positionArray[posCounter]=i;
				positionArray[posCounter+1]=j;
				positionArray[posCounter+2]=0.0;
				textureArray[texPosCounter]=0.0;
				textureArray[texPosCounter+1]=0.0;
				//Vertice 2
				positionArray[posCounter+3]=i+tamTex;
				positionArray[posCounter+4]=j;
				positionArray[posCounter+5]=0.0;
				textureArray[texPosCounter+2]=1.0;
				textureArray[texPosCounter+3]=0.0;
				//Vertice 3
				positionArray[posCounter+6]=i+tamTex;
				positionArray[posCounter+7]=j+tamTex;
				positionArray[posCounter+8]=0.0;
				textureArray[texPosCounter+4]=1.0;
				textureArray[texPosCounter+5]=1.0;

				//Segundo triangulo
				posCounter+=9;
				texPosCounter+=6;
				//Vertice 1
				positionArray[posCounter]=i;
				positionArray[posCounter+1]=j;
				positionArray[posCounter+2]=0.0;
				textureArray[texPosCounter]=0.0;
				textureArray[texPosCounter+1]=0.0;
				//Vertice 2
				positionArray[posCounter+3]=i;
				positionArray[posCounter+4]=j+tamTex;
				positionArray[posCounter+5]=0.0;
				textureArray[texPosCounter+2]=0.0;
				textureArray[texPosCounter+3]=1.0;
				//Vertice 3
				positionArray[posCounter+6]=i+tamTex;
				positionArray[posCounter+7]=j+tamTex;
				positionArray[posCounter+8]=0.0;
				textureArray[texPosCounter+4]=1.0;
				textureArray[texPosCounter+5]=1.0;

				posCounter+=9;
				texPosCounter+=6;

				cantTriangulos+=2;

			}
	}

	for(int i = 0; i<(cantTriangulos*3); i++){
		colorArray[i*3]=0.0;
		colorArray[(i*3)+1]=1.0;
		colorArray[(i*3)+2]=0.0;
		normalArray[i*3]=0.0;
		normalArray[(i*3)+1]=0.0;
		normalArray[(i*3)+2]=1.0;
	}

	glGenBuffers(1, &bufferPositionHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferPositionHandler);
	glBufferData( GL_ARRAY_BUFFER, (cantTriangulos * 9) * sizeof (float), this->positionArray, GL_STATIC_DRAW );

	glGenBuffers(1, &bufferColorHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferColorHandler);
	glBufferData( GL_ARRAY_BUFFER, (cantTriangulos * 9) * sizeof (float), this->colorArray, GL_STATIC_DRAW );

	glGenBuffers(1, &bufferNormalHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferNormalHandler);
	glBufferData( GL_ARRAY_BUFFER, (cantTriangulos * 9) * sizeof (float), this->normalArray, GL_STATIC_DRAW );

	glGenBuffers(1, &bufferTextureHandler);
	glBindBuffer( GL_ARRAY_BUFFER, bufferTextureHandler);
	glBufferData( GL_ARRAY_BUFFER, (cantTriangulos * 6) * sizeof (float), this->textureArray, GL_STATIC_DRAW );
}

void RectangRef::print(){
	program->setTexture(this->texId);
	program->setActualProgram();

	glBindBuffer( GL_ARRAY_BUFFER, bufferNormalHandler);
	glVertexAttribPointer( VERTEX_NOR_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferColorHandler);
	glVertexAttribPointer( VERTEX_COL_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferPositionHandler);
	glVertexAttribPointer( VERTEX_POS_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferTextureHandler);
	glVertexAttribPointer( VERTEX_TEX_ATTR_INDEX, 2 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glDrawArrays( GL_TRIANGLES, 0, cantTriangulos * 3);
}

RectangRef::~RectangRef() {
	// TODO Auto-generated destructor stub
}

