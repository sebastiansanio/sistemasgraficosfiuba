/*
 * Rectangle.cpp
 *
 *  Created on: 27/01/2012
 *      Author: damian
 */

#include "Rectang.h"

Rectang::Rectang(float xSize, float ySize,double tamPaso) {
	int cantTriangulos = 0;

	//No podemos confiar en este calculo de triangulos porque el float tiene error
	int cantTriangulosEstimado = (xSize*2/tamPaso)*(ySize*2/tamPaso)*2;
	cantTriangulosEstimado = cantTriangulosEstimado * 2;

	float* positionArray = new float[cantTriangulosEstimado*9];
	float* colorArray = new float[cantTriangulosEstimado*9];
	float* normalArray = new float[cantTriangulosEstimado*9];

	int posCounter = 0;

	for(float i = -(xSize); i < (xSize); i+=tamPaso) {
			for(float j = -(ySize); j < (ySize); j+=tamPaso){
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

	this->generic = new Generic(cantTriangulos,positionArray,colorArray,normalArray);
}

void Rectang::print(){
	this->generic->print();
}

Rectang::~Rectang() {
	// TODO Auto-generated destructor stub
}

