/*
 * RectangTex.cpp
 *
 *  Created on: 27/01/2012
 *      Author: damian
 */

#include "RectangRef.h"

RectangRef::RectangRef(float xSize, float ySize,double tamTex) {
	// TODO Auto-generated constructor stub
	int cantTriangulos = 0;

	int cantTriangulosEstimado = (xSize*2/tamTex)*(ySize*2/tamTex)*2;
	cantTriangulosEstimado = cantTriangulosEstimado * 2;

	float* positionArray = new float[cantTriangulosEstimado*9];
	float* colorArray = new float[cantTriangulosEstimado*9];
	float* normalArray = new float[cantTriangulosEstimado*9];
	float* textureArray = new float[cantTriangulosEstimado*6];

	int posCounter = 0;
	int texPosCounter = 0;

	for(float i = -(xSize); i < (xSize); i+=tamTex) {
			for(float j = -(ySize); j < (ySize); j+=tamTex){
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

	this->genericRef = new GenericRef(cantTriangulos,positionArray,colorArray,normalArray,textureArray);

}

void RectangRef::print(){
	this->genericRef->print();
}

RectangRef::~RectangRef() {
	// TODO Auto-generated destructor stub
}

