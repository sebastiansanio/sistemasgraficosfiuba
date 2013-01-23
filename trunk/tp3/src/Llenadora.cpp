/*
 * Llenadora.cpp
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#include "Llenadora.h"
#define LLENA_SUP 2.5
#define LLENA_INF 2.25
#define LLENA_VELOCIDAD 0.02
#define PI 3.14159265
#define STEP_LLENA 10

Llenadora::Llenadora() {
	this->cubeRef = new CubeRef(1.0,1.0,1.0);
//	this->portaEtiqueta = new PortaEtiqueta();
	this->posLlenadora = LLENA_SUP;
	this->moviendo=false;

	//Dibujo el tanque de la llenadora, es una superficie de revolucion

	int cantTriangulos = 0;

	vector<Coordinate*>* points = new vector<Coordinate*>;

	points->push_back(new Coordinate(0.0,0.0,0.0));
	points->push_back(new Coordinate(0.0,0.1,0.01));
	points->push_back(new Coordinate(0.0,0.2,0.025));
	points->push_back(new Coordinate(0.0,0.3,0.0475));
	points->push_back(new Coordinate(0.0,0.4,0.08125));
	points->push_back(new Coordinate(0.0,0.5,0.131875));
	points->push_back(new Coordinate(0.0,0.5,1.183125));
	points->push_back(new Coordinate(0.0,0.4,1.23375));
	points->push_back(new Coordinate(0.0,0.3,1.2675));
	points->push_back(new Coordinate(0.0,0.2,1.275));
	points->push_back(new Coordinate(0.0,0.1,1.29));
	points->push_back(new Coordinate(0.0,0.0,1.3));

	//No podemos confiar en este calculo de triangulos porque el float tiene error
	int cantTriangulosEstimado = ((360/STEP_LLENA)+1) * (points->size()-1) * 2;

	float* positionArray = new float[cantTriangulosEstimado*9];
	float* colorArray = new float[cantTriangulosEstimado*9];
	float* normalArray = new float[cantTriangulosEstimado*9];

	int posCounter = 0;

	float pendiente = 0;
	float zNormal = 0;

	for(unsigned int i=0;i<points->size()-1;i++) {

		pendiente = ( points->at(i+1)->getZ() - points->at(i)->getZ() ) / ( points->at(i+1)->getY() - points->at(i)->getY() );

		zNormal = -1/pendiente;

			for(float j=0;j<360;j=j+STEP_LLENA){
				//Primer triangulo
				//Vertice 1
				positionArray[posCounter]=points->at(i)->getY()*cos(PI*j/180);
				positionArray[posCounter+1]=points->at(i)->getY()*sin(PI*j/180);
				positionArray[posCounter+2]=points->at(i)->getZ();
				normalArray[posCounter]=cos(PI*j/180);
				normalArray[posCounter+1]=sin(PI*j/180);
				normalArray[posCounter+2]=zNormal;
				//Vertice 2
				positionArray[posCounter+3]=points->at(i)->getY()*cos(PI*(j+STEP_LLENA)/180);
				positionArray[posCounter+4]=points->at(i)->getY()*sin(PI*(j+STEP_LLENA)/180);
				positionArray[posCounter+5]=points->at(i)->getZ();
				normalArray[posCounter+3]=cos(PI*(j+STEP_LLENA)/180);
				normalArray[posCounter+4]=sin(PI*(j+STEP_LLENA)/180);
				normalArray[posCounter+5]=zNormal;
				//Vertice 3
				positionArray[posCounter+6]=points->at(i+1)->getY()*cos(PI*(j+STEP_LLENA)/180);
				positionArray[posCounter+7]=points->at(i+1)->getY()*sin(PI*(j+STEP_LLENA)/180);
				positionArray[posCounter+8]=points->at(i+1)->getZ();
				normalArray[posCounter+6]=cos(PI*(j+STEP_LLENA)/180);
				normalArray[posCounter+7]=sin(PI*(j+STEP_LLENA)/180);
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
				positionArray[posCounter+6]=points->at(i+1)->getY()*cos(PI*(j+STEP_LLENA)/180);
				positionArray[posCounter+7]=points->at(i+1)->getY()*sin(PI*(j+STEP_LLENA)/180);
				positionArray[posCounter+8]=points->at(i+1)->getZ();
				normalArray[posCounter+6]=cos(PI*(j+STEP_LLENA)/180);
				normalArray[posCounter+7]=sin(PI*(j+STEP_LLENA)/180);
				normalArray[posCounter+8]=zNormal;

				posCounter=posCounter+9;

				cantTriangulos+=2;

			}
	}

	int verticesSeccion = (360/STEP_LLENA) * 2 * 3;
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

		colorArray[i*3]=0.257;
		colorArray[(i*3)+1]=0.863;
		colorArray[(i*3)+2]=0.773;
	}

	this->tanque = new Generic(cantTriangulos,positionArray,colorArray,normalArray);

	//Dibujo la canilla de la llenadora, es una superficie de revolucion

	cantTriangulos = 0;

	points = new vector<Coordinate*>;

	points->push_back(new Coordinate(0.0,0.0,0.0));
	points->push_back(new Coordinate(0.0,0.05,0.0));
	points->push_back(new Coordinate(0.0,0.05,1.5));
	points->push_back(new Coordinate(0.0,0.0,1.5));

	//No podemos confiar en este calculo de triangulos porque el float tiene error
	cantTriangulosEstimado = ((360/STEP_LLENA)+1) * (points->size()-1) * 2;

	positionArray = new float[cantTriangulosEstimado*9];
	colorArray = new float[cantTriangulosEstimado*9];
	normalArray = new float[cantTriangulosEstimado*9];

	posCounter = 0;

	pendiente = 0;
	zNormal = 0;

	for(unsigned int i=0;i<points->size()-1;i++) {

		pendiente = ( points->at(i+1)->getZ() - points->at(i)->getZ() ) / ( points->at(i+1)->getY() - points->at(i)->getY() );

		zNormal = -1/pendiente;

			for(float j=0;j<360;j=j+STEP_LLENA){
				//Primer triangulo
				//Vertice 1
				positionArray[posCounter]=points->at(i)->getY()*cos(PI*j/180);
				positionArray[posCounter+1]=points->at(i)->getY()*sin(PI*j/180);
				positionArray[posCounter+2]=points->at(i)->getZ();
				normalArray[posCounter]=cos(PI*j/180);
				normalArray[posCounter+1]=sin(PI*j/180);
				normalArray[posCounter+2]=zNormal;
				//Vertice 2
				positionArray[posCounter+3]=points->at(i)->getY()*cos(PI*(j+STEP_LLENA)/180);
				positionArray[posCounter+4]=points->at(i)->getY()*sin(PI*(j+STEP_LLENA)/180);
				positionArray[posCounter+5]=points->at(i)->getZ();
				normalArray[posCounter+3]=cos(PI*(j+STEP_LLENA)/180);
				normalArray[posCounter+4]=sin(PI*(j+STEP_LLENA)/180);
				normalArray[posCounter+5]=zNormal;
				//Vertice 3
				positionArray[posCounter+6]=points->at(i+1)->getY()*cos(PI*(j+STEP_LLENA)/180);
				positionArray[posCounter+7]=points->at(i+1)->getY()*sin(PI*(j+STEP_LLENA)/180);
				positionArray[posCounter+8]=points->at(i+1)->getZ();
				normalArray[posCounter+6]=cos(PI*(j+STEP_LLENA)/180);
				normalArray[posCounter+7]=sin(PI*(j+STEP_LLENA)/180);
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
				positionArray[posCounter+6]=points->at(i+1)->getY()*cos(PI*(j+STEP_LLENA)/180);
				positionArray[posCounter+7]=points->at(i+1)->getY()*sin(PI*(j+STEP_LLENA)/180);
				positionArray[posCounter+8]=points->at(i+1)->getZ();
				normalArray[posCounter+6]=cos(PI*(j+STEP_LLENA)/180);
				normalArray[posCounter+7]=sin(PI*(j+STEP_LLENA)/180);
				normalArray[posCounter+8]=zNormal;

				posCounter=posCounter+9;

				cantTriangulos+=2;

			}
	}

	verticesSeccion = (360/STEP_LLENA) * 2 * 3;

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

		colorArray[i*3]=1.0;
		colorArray[(i*3)+1]=1.0;
		colorArray[(i*3)+2]=1.0;

	}

	this->cilindro = new Generic(cantTriangulos,positionArray,colorArray,normalArray);

	//Hacer el toroide

	cantTriangulos = 0;

	points = new vector<Coordinate*>;

	points->push_back(new Coordinate(0.0,0.0,0.0));
	points->push_back(new Coordinate(0.0,0.05,0.0));
	points->push_back(new Coordinate(0.0,0.05,1.5));
	points->push_back(new Coordinate(0.0,0.0,1.5));

	//No podemos confiar en este calculo de triangulos porque el float tiene error
	cantTriangulosEstimado = ((2*PI)/(PI/10)) * ((2*PI)/(PI/10)) * 2 * 8;

	positionArray = new float[cantTriangulosEstimado*9];
	colorArray = new float[cantTriangulosEstimado*9];
	normalArray = new float[cantTriangulosEstimado*9];

	posCounter = 0;

	for(float beta = 0; beta < (PI/2); beta+=(PI/10)) {
		for(float alfa = 0; alfa < (2*PI); alfa+=(PI/10)){
			float radio1 = 0.2;
			float radio2 = 0.05;
			float cosalfa = cos(alfa);
			float cosbeta = cos(beta);
			float cosalfapaso = cos(alfa+(PI/10));
			float cosbetapaso = cos(beta+(PI/10));
			float sinalfa = sin(alfa);
			float sinbeta = sin(beta);
			float sinalfapaso = sin(alfa+(PI/10));
			float sinbetapaso = sin(beta+(PI/10));

			//Primer triangulo
			//Vertice 1
			positionArray[posCounter]= (radio1 + radio2 * cosalfa) * cosbeta;
			positionArray[posCounter+1]= (radio1 + radio2 * cosalfa) * sinbeta;
			positionArray[posCounter+2]= radio2 * sinalfa;
			normalArray[posCounter]= (radio2 * cosalfa) * cosbeta;
			normalArray[posCounter+1]= (radio2 * cosalfa) * sinbeta;
			normalArray[posCounter+2]= radio2 * sinalfa;
			//Vertice 2
			positionArray[posCounter+3]= (radio1 + radio2 * cosalfapaso) * cosbeta;
			positionArray[posCounter+4]= (radio1 + radio2 * cosalfapaso) * sinbeta;
			positionArray[posCounter+5]= radio2 * sinalfapaso;
			normalArray[posCounter+3]= (radio2 * cosalfapaso) * cosbeta;
			normalArray[posCounter+4]= (radio2 * cosalfapaso) * sinbeta;
			normalArray[posCounter+5]= radio2 * sinalfapaso;
			//Vertice 3
			positionArray[posCounter+6]= (radio1 + radio2 * cosalfapaso) * cosbetapaso;
			positionArray[posCounter+7]= (radio1 + radio2 * cosalfapaso) * sinbetapaso;
			positionArray[posCounter+8]= radio2 * sinalfapaso;
			normalArray[posCounter+6]= (radio2 * cosalfapaso) * cosbetapaso;
			normalArray[posCounter+7]= (radio2 * cosalfapaso) * sinbetapaso;
			normalArray[posCounter+8]= radio2 * sinalfapaso;

			//Segundo triangulo
			posCounter=posCounter+9;
			//Vertice 1
			positionArray[posCounter]= (radio1 + radio2 * cosalfa) * cosbeta;
			positionArray[posCounter+1]= (radio1 + radio2 * cosalfa) * sinbeta;
			positionArray[posCounter+2]= radio2 * sinalfa;
			normalArray[posCounter]= (radio2 * cosalfa) * cosbeta;
			normalArray[posCounter+1]= (radio2 * cosalfa) * sinbeta;
			normalArray[posCounter+2]= radio2 * sinalfa;
			//Vertice 2
			positionArray[posCounter+3]= (radio1 + radio2 * cosalfa) * cosbetapaso;
			positionArray[posCounter+4]= (radio1 + radio2 * cosalfa) * sinbetapaso;
			positionArray[posCounter+5]= radio2 * sinalfa;
			normalArray[posCounter+3]= (radio2 * cosalfa) * cosbetapaso;
			normalArray[posCounter+4]= (radio2 * cosalfa) * sinbetapaso;
			normalArray[posCounter+5]= radio2 * sinalfa;
			//Vertice 3
			positionArray[posCounter+6]= (radio1 + radio2 * cosalfapaso) * cosbetapaso;
			positionArray[posCounter+7]= (radio1 + radio2 * cosalfapaso) * sinbetapaso;
			positionArray[posCounter+8]= radio2 * sinalfapaso;
			normalArray[posCounter+6]= (radio2 * cosalfapaso) * cosbetapaso;
			normalArray[posCounter+7]= (radio2 * cosalfapaso) * sinbetapaso;
			normalArray[posCounter+8]= radio2 * sinalfapaso;

			posCounter=posCounter+9;

			cantTriangulos+=2;

		}
	}

	for(int i = 0; i<(cantTriangulos*3); i++){

		colorArray[i*3]=1.0;
		colorArray[(i*3)+1]=1.0;
		colorArray[(i*3)+2]=1.0;

	}

	this->toroide = new Generic(cantTriangulos,positionArray,colorArray,normalArray);

}

void Llenadora::print() {
	glPushMatrix();
		glTranslatef(0.0,0.0,0.6);
		glScalef(0.3,0.3,0.4);
		cubeRef->print();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0,0.0,0.8);
		tanque->print();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0,0.0,2.3);
		glScalef(0.2,0.2,0.3);
		cubeRef->print();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0,-0.2,this->posLlenadora);
		glPushMatrix();
			glRotatef(90,1,0,0);
			cilindro->print();
			glTranslatef(0.0,-0.2,1.5);
			glRotatef(90,1,0,0);
			glRotatef(90,0,1,0);
			toroide->print();
		glPopMatrix();
		glTranslatef(0.0,-1.70,-0.25);
		glScalef(1.5,1.5,0.05);
		cilindro->print();
	glPopMatrix();
}

void Llenadora::start() {
	if(!moviendo) {
		this->moviendo = true;
		this->subiendo = false;
		this->posLlenadora = LLENA_SUP - LLENA_VELOCIDAD;
	}
}

void Llenadora::mover() {
	if(this->moviendo) {
		if(this->posLlenadora >= LLENA_SUP) {
			this->subiendo = false;
			this->moviendo = false;
		} else if (this->posLlenadora <= LLENA_INF) {
			this->subiendo = true;
		}

		if(this->subiendo) {
			this->posLlenadora += LLENA_VELOCIDAD;
		} else {
			this->posLlenadora -= LLENA_VELOCIDAD;
		}
	}
}

Llenadora::~Llenadora() {
	// TODO Auto-generated destructor stub
}

