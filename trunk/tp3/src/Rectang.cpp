/*
 * Rectangle.cpp
 *
 *  Created on: 27/01/2012
 *      Author: damian
 */

#include "Rectang.h"

Rectang::Rectang(float xSize, float ySize,double tamPaso) {
	this->x = xSize;
	this->y = ySize;
	this->tamPaso = tamPaso;
	this->program = BasicProgram::Instance();
	this->cantTriangulos = 0;

	//No podemos confiar en este calculo de triangulos porque el float tiene error
	int cantTriangulosEstimado = (xSize*2/tamPaso)*(ySize*2/tamPaso)*2;
	cantTriangulosEstimado = cantTriangulosEstimado * 2;
	this->positionArray = new float[cantTriangulosEstimado*9];
	this->colorArray = new float[cantTriangulosEstimado*9];
	this->normalArray = new float[cantTriangulosEstimado*9];

	int posCounter = 0;

	for(float i = -(this->x); i < (this->x); i+=tamPaso) {
			for(float j = -(this->y); j < (this->y); j+=tamPaso){
				//Primer triangulo
				//Vertice 1
				positionArray[posCounter]=i;
				positionArray[posCounter+1]=j;
				positionArray[posCounter+2]=0.0;
				//Vertice 2
				positionArray[posCounter+3]=i+tamPaso;
				positionArray[posCounter+4]=j;
				positionArray[posCounter+5]=0.0;
				//Vertice 3
				positionArray[posCounter+6]=i+tamPaso;
				positionArray[posCounter+7]=j+tamPaso;
				positionArray[posCounter+8]=0.0;

				//Segundo triangulo
				posCounter=posCounter+9;
				//Vertice 1
				positionArray[posCounter]=i;
				positionArray[posCounter+1]=j;
				positionArray[posCounter+2]=0.0;
				//Vertice 2
				positionArray[posCounter+3]=i;
				positionArray[posCounter+4]=j+tamPaso;
				positionArray[posCounter+5]=0.0;
				//Vertice 3
				positionArray[posCounter+6]=i+tamPaso;
				positionArray[posCounter+7]=j+tamPaso;
				positionArray[posCounter+8]=0.0;

				posCounter=posCounter+9;

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
}

void Rectang::print(){
	program->setActualProgram();

	glBindBuffer( GL_ARRAY_BUFFER, bufferNormalHandler);
	glVertexAttribPointer( VERTEX_NOR_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferColorHandler);
	glVertexAttribPointer( VERTEX_COL_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer( GL_ARRAY_BUFFER, bufferPositionHandler);
	glVertexAttribPointer( VERTEX_POS_ATTR_INDEX, 3 , GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glDrawArrays( GL_TRIANGLES, 0, cantTriangulos * 3);

}

Rectang::~Rectang() {
	// TODO Auto-generated destructor stub
}

