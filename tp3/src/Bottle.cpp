#include "Bottle.h"
#define PI 3.14159265

Bottle::Bottle(){
	program = BasicProgram::Instance();
	bezier=new Bezier();
	bezier->addPoint(0,0,0);
	bezier->addPoint(0,0.3,0);
	bezier->addPoint(0,0.27,0.8);
	bezier->addPoint(0,0.3,1.2);
	bezier->addPoint(0,0.15,1.6);
	bezier->addPoint(0,0.12,1.8);
	bezier->addPoint(0,0.1,2);
	bezier->calculate();
}
void Bottle::print(){
	//program->setTexture(0);
	program->setActualProgram();
	program->updateModelViewProjection();


	vector<Coordinate*>* points= bezier->getPoints();
	//Ver esto
	float step = 10;

	for(unsigned int i=0;i<points->size()-1;i++){
		for(float j=0;j<=350;j=j+step){
			program->setPositionValue(0,points->at(i)->getY()*cos(PI*j/180));
			program->setPositionValue(1,points->at(i)->getY()*sin(PI*j/180));
			program->setPositionValue(2,points->at(i)->getZ());
			program->setPositionValue(3,points->at(i)->getY()*cos(PI*(j+step)/180));
			program->setPositionValue(4,points->at(i)->getY()*sin(PI*(j+step)/180));
			program->setPositionValue(5,points->at(i)->getZ());
			program->setPositionValue(6,points->at(i+1)->getY()*cos(PI*j/180));
			program->setPositionValue(7,points->at(i+1)->getY()*sin(PI*j/180));
			program->setPositionValue(8,points->at(i+1)->getZ());
			program->drawTriangle();

			program->setPositionValue(0,points->at(i+1)->getY()*cos(PI*j/180));
			program->setPositionValue(1,points->at(i+1)->getY()*sin(PI*j/180));
			program->setPositionValue(2,points->at(i+1)->getZ());
			program->setPositionValue(3,points->at(i)->getY()*cos(PI*(j+step)/180));
			program->setPositionValue(4,points->at(i)->getY()*sin(PI*(j+step)/180));
			program->setPositionValue(5,points->at(i)->getZ());
			program->setPositionValue(6,points->at(i+1)->getY()*cos(PI*(j+step)/180));
			program->setPositionValue(7,points->at(i+1)->getY()*sin(PI*(j+step)/180));
			program->setPositionValue(8,points->at(i+1)->getZ());
			program->drawTriangle();
		}

	}

}
Bottle::~Bottle(){

}
