/*
 * Lampara.cpp
 *
 *  Created on: Jan 16, 2013
 *      Author: damian
 */

#include "Lampara.h"

#define PI 3.14159265
#define STEP_LAMP 10

Lampara::Lampara() {
	int cantTriangulos = 0;

	vector<Coordinate*>* points = new vector<Coordinate*>;

	points->push_back(new Coordinate(0.0,0.2,0.0));
	points->push_back(new Coordinate(0.0,0.2,0.5));
	points->push_back(new Coordinate(0.0,0.05,0.5));
	points->push_back(new Coordinate(0.0,0.06,4.0));
	points->push_back(new Coordinate(0.0,1.0,5.0));
	points->push_back(new Coordinate(0.0,1.0,5.2));
	points->push_back(new Coordinate(0.0,0.0,5.0));

	//No podemos confiar en este calculo de triangulos porque el float tiene error
	int cantTriangulosEstimado = ((360/STEP_LAMP)+1) * (points->size()-1) * 2;

	float* positionArray = new float[cantTriangulosEstimado*9];
	float* colorArray = new float[cantTriangulosEstimado*9];
	float* normalArray = new float[cantTriangulosEstimado*9];

	int posCounter = 0;

	float pendiente = 0;
	float zNormal = 0;

	for(unsigned int i=0;i<points->size()-1;i++) {

		pendiente = ( points->at(i+1)->getZ() - points->at(i)->getZ() ) / ( points->at(i+1)->getY() - points->at(i)->getY() );

		zNormal = -1/pendiente;

		cout << "Pendiente: " << pendiente << " Normal: " << -1/pendiente << endl;

			for(float j=0;j<360;j=j+STEP_LAMP){
				//Primer triangulo
				//Vertice 1
				positionArray[posCounter]=points->at(i)->getY()*cos(PI*j/180);
				positionArray[posCounter+1]=points->at(i)->getY()*sin(PI*j/180);
				positionArray[posCounter+2]=points->at(i)->getZ();
				normalArray[posCounter]=cos(PI*j/180);
				normalArray[posCounter+1]=sin(PI*j/180);
				normalArray[posCounter+2]=zNormal;
				//Vertice 2
				positionArray[posCounter+3]=points->at(i)->getY()*cos(PI*(j+STEP_LAMP)/180);
				positionArray[posCounter+4]=points->at(i)->getY()*sin(PI*(j+STEP_LAMP)/180);
				positionArray[posCounter+5]=points->at(i)->getZ();
				normalArray[posCounter+3]=cos(PI*(j+STEP_LAMP)/180);
				normalArray[posCounter+4]=sin(PI*(j+STEP_LAMP)/180);
				normalArray[posCounter+5]=zNormal;
				//Vertice 3
				positionArray[posCounter+6]=points->at(i+1)->getY()*cos(PI*(j+STEP_LAMP)/180);
				positionArray[posCounter+7]=points->at(i+1)->getY()*sin(PI*(j+STEP_LAMP)/180);
				positionArray[posCounter+8]=points->at(i+1)->getZ();
				normalArray[posCounter+6]=cos(PI*(j+STEP_LAMP)/180);
				normalArray[posCounter+7]=sin(PI*(j+STEP_LAMP)/180);
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
				positionArray[posCounter+6]=points->at(i+1)->getY()*cos(PI*(j+STEP_LAMP)/180);
				positionArray[posCounter+7]=points->at(i+1)->getY()*sin(PI*(j+STEP_LAMP)/180);
				positionArray[posCounter+8]=points->at(i+1)->getZ();
				normalArray[posCounter+6]=cos(PI*(j+STEP_LAMP)/180);
				normalArray[posCounter+7]=sin(PI*(j+STEP_LAMP)/180);
				normalArray[posCounter+8]=zNormal;

				posCounter=posCounter+9;

				cantTriangulos+=2;

			}
	}

	int verticesSeccion = (360/STEP_LAMP) * 2 * 3;
	int seccion;
	for(int i = 0; i<(cantTriangulos*3); i++){
		// i es el numero de vertice
		seccion = i / verticesSeccion;

		if(seccion == 0 or seccion == 1 or seccion == 3) {
			colorArray[i*3]=0.8;
			colorArray[(i*3)+1]=0.8;
			colorArray[(i*3)+2]=0.8;
		} else if (seccion == 5) {
			colorArray[i*3]=1.0;
			colorArray[(i*3)+1]=1.0;
			colorArray[(i*3)+2]=1.0;
		} else {
			colorArray[i*3]=0.5;
			colorArray[(i*3)+1]=0.5;
			colorArray[(i*3)+2]=0.5;
		}
	}

	this->generic = new Generic(cantTriangulos,positionArray,colorArray,normalArray);

}

void Lampara::print(){
	this->generic->print();
}

Lampara::~Lampara() {
	// TODO Auto-generated destructor stub
}

