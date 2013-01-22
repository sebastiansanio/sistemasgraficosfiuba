/*
 * PortaEtiqueta.cpp
 *
 *  Created on: Jan 16, 2013
 *      Author: damian
 */

#include "PortaEtiqueta.h"

#define PI 3.14159265
#define STEP_ETI 10

PortaEtiqueta::PortaEtiqueta() {
	int cantTriangulos = 0;

	vector<Coordinate*>* points = new vector<Coordinate*>;

	points->push_back(new Coordinate(0.0,0.0,0.0));
	points->push_back(new Coordinate(0.0,0.2,0.0));
	points->push_back(new Coordinate(0.0,0.22,0.0));
	points->push_back(new Coordinate(0.0,0.22,0.5));
	points->push_back(new Coordinate(0.0,0.25,0.5));
	points->push_back(new Coordinate(0.0,0.25,1.0));
	points->push_back(new Coordinate(0.0,0.0,1.0));

	//No podemos confiar en este calculo de triangulos porque el float tiene error
	int cantTriangulosEstimado = ((360/STEP_ETI)+1) * (points->size()-1) * 2;

	float* positionArray = new float[cantTriangulosEstimado*9];
	float* colorArray = new float[cantTriangulosEstimado*9];
	float* normalArray = new float[cantTriangulosEstimado*9];

	int posCounter = 0;

	float pendiente = 0;
	float zNormal = 0;

	for(unsigned int i=0;i<points->size()-1;i++) {

		pendiente = ( points->at(i+1)->getZ() - points->at(i)->getZ() ) / ( points->at(i+1)->getY() - points->at(i)->getY() );

		zNormal = -1/pendiente;

			for(float j=0;j<360;j=j+STEP_ETI){
				//Primer triangulo
				//Vertice 1
				positionArray[posCounter]=points->at(i)->getY()*cos(PI*j/180);
				positionArray[posCounter+1]=points->at(i)->getY()*sin(PI*j/180);
				positionArray[posCounter+2]=points->at(i)->getZ();
				normalArray[posCounter]=cos(PI*j/180);
				normalArray[posCounter+1]=sin(PI*j/180);
				normalArray[posCounter+2]=zNormal;
				//Vertice 2
				positionArray[posCounter+3]=points->at(i)->getY()*cos(PI*(j+STEP_ETI)/180);
				positionArray[posCounter+4]=points->at(i)->getY()*sin(PI*(j+STEP_ETI)/180);
				positionArray[posCounter+5]=points->at(i)->getZ();
				normalArray[posCounter+3]=cos(PI*(j+STEP_ETI)/180);
				normalArray[posCounter+4]=sin(PI*(j+STEP_ETI)/180);
				normalArray[posCounter+5]=zNormal;
				//Vertice 3
				positionArray[posCounter+6]=points->at(i+1)->getY()*cos(PI*(j+STEP_ETI)/180);
				positionArray[posCounter+7]=points->at(i+1)->getY()*sin(PI*(j+STEP_ETI)/180);
				positionArray[posCounter+8]=points->at(i+1)->getZ();
				normalArray[posCounter+6]=cos(PI*(j+STEP_ETI)/180);
				normalArray[posCounter+7]=sin(PI*(j+STEP_ETI)/180);
				normalArray[posCounter+8]=zNormal;

				//Segundo triangulo
				posCounter=posCounter+9;
				//Vertice 1
				positionArray[posCounter]=points->at(i)->getY()*cos(PI*j/180);
				positionArray[posCounter+1]=points->at(i)->getY()*sin(PI*j/180);
				positionArray[posCounter+2]=points->at(i)->getZ();
				normalArray[posCounter]=cos(PI*j/180);
				normalArray[posCounter+1]=sin(PI*j/180);
				normalArray[posCounter+2]=zNormal;
				//Vertice 2
				positionArray[posCounter+3]=points->at(i+1)->getY()*cos(PI*j/180);
				positionArray[posCounter+4]=points->at(i+1)->getY()*sin(PI*j/180);
				positionArray[posCounter+5]=points->at(i+1)->getZ();
				normalArray[posCounter+3]=cos(PI*j/180);
				normalArray[posCounter+4]=sin(PI*j/180);
				normalArray[posCounter+5]=zNormal;
				//Vertice 3
				positionArray[posCounter+6]=points->at(i+1)->getY()*cos(PI*(j+STEP_ETI)/180);
				positionArray[posCounter+7]=points->at(i+1)->getY()*sin(PI*(j+STEP_ETI)/180);
				positionArray[posCounter+8]=points->at(i+1)->getZ();
				normalArray[posCounter+6]=cos(PI*(j+STEP_ETI)/180);
				normalArray[posCounter+7]=sin(PI*(j+STEP_ETI)/180);
				normalArray[posCounter+8]=zNormal;

				posCounter=posCounter+9;

				cantTriangulos+=2;

			}
	}

	int verticesSeccion = (360/STEP_ETI) * 2 * 3;
	int seccion;
	for(int i = 0; i<(cantTriangulos*3); i++){
		// i es el numero de vertice
		seccion = i / verticesSeccion;

		//Si es una superficie plana en z corrigo la normal
		if(normalArray[(i*3)+2] > 10000000) {
			normalArray[(i*3)] = 0.0;
			normalArray[(i*3)+1] = 0.0;
			normalArray[(i*3)+2] = 1.0;
		} else if (normalArray[(i*3)+2] < -10000000) {
			normalArray[(i*3)] = 0.0;
			normalArray[(i*3)+1] = 0.0;
			normalArray[(i*3)+2] = -1.0;
		}

		if(seccion == 0) {
			colorArray[i*3]=0.0;
			colorArray[(i*3)+1]=0.0;
			colorArray[(i*3)+2]=0.0;

		} else if (seccion == 5) {
			colorArray[i*3]=0.846;
			colorArray[(i*3)+1]=0.471;
			colorArray[(i*3)+2]=0.232;
		} else {
			colorArray[i*3]=0.846;
			colorArray[(i*3)+1]=0.471;
			colorArray[(i*3)+2]=0.232;
		}
	}

	this->generic = new Generic(cantTriangulos,positionArray,colorArray,normalArray);

}

void PortaEtiqueta::print(){
	this->generic->print();
}

PortaEtiqueta::~PortaEtiqueta() {
	// TODO Auto-generated destructor stub
}

