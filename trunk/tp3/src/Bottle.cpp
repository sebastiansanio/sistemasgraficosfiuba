#include "Bottle.h"
#define PI 3.14159265

Bottle::Bottle(){
	program = TextureProgram::Instance();
	bezier=new Bezier();
	bezier->addPoint(0,0,0);
	bezier->addPoint(1,1,1);
	bezier->addPoint(2,2,2);
	bezier->addPoint(3,3,3);
	bezier->calculate();
}
void Bottle::print(){
	program->setTexture(1);
	program->setActualProgram();
	program->updateModelViewProjection();

	Coordinate* coordinate1;
	Coordinate* coordinate2;
	Coordinate* coordinate3;
	coordinate1=bezier->getPoint();


	//Ver esto
	while(!bezier->isEmpty()){

		coordinate2=bezier->getPoint();
		coordinate3=coordinate2;
		for(float j=0;j<=360;j=j+10){
			program->setPositionValue(0,coordinate1->getX());
			program->setPositionValue(1,coordinate1->getY());
			program->setPositionValue(2,coordinate1->getZ());
			program->setPositionValue(3,coordinate2->getX());
			program->setPositionValue(4,coordinate2->getY());
			program->setPositionValue(5,coordinate2->getZ());
			program->setPositionValue(6,coordinate3->getX());
			program->setPositionValue(7,coordinate3->getY());
			program->setPositionValue(8,coordinate3->getZ());
			program->drawTriangle();
		}

		coordinate1=coordinate2;
	}


}
Bottle::~Bottle(){

}
