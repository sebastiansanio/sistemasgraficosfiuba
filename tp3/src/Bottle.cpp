#include "Bottle.h"
#define PI 3.14159265

Bottle::Bottle(){
	program = TextureProgram::Instance();
	bezier=new Bezier();
	bezier->addPoint(0,0,0);
	bezier->addPoint(0,3,3);
	bezier->addPoint(0,6,6);
	bezier->addPoint(0,9,9);
	bezier->addPoint(0,6,10);
	bezier->addPoint(0,5,11);
	bezier->addPoint(0,0,13);
	bezier->calculate();
}
void Bottle::print(){
	program->setTexture(1);
	program->setActualProgram();
	program->updateModelViewProjection();

	Coordinate* coordinate1;

	//Ver esto
	while(!bezier->isEmpty()){

		coordinate1=bezier->getPoint();

//		for(float j=0;j<=360;j=j+1){
//			program->setPositionValue(0,coordinate1->getX()*cos(PI*j/180));
//			program->setPositionValue(1,coordinate1->getY()*sin(PI*j/180));
//			program->setPositionValue(2,coordinate1->getZ());
//			program->setPositionValue(3,coordinate1->getX()*cos(PI*j/180));
//			program->setPositionValue(4,coordinate1->getY()*sin(PI*j/180));
//			program->setPositionValue(5,coordinate1->getZ());
//			program->setPositionValue(6,coordinate1->getX()*cos(PI*j/180));
//			program->setPositionValue(7,coordinate1->getY()*sin(PI*j/180));
//			program->setPositionValue(8,coordinate1->getZ());
//			program->drawPoints();
//		}


		program->setPositionValue(0,coordinate1->getX());
		program->setPositionValue(1,coordinate1->getY());
		program->setPositionValue(2,coordinate1->getZ());
		program->setPositionValue(3,coordinate1->getX());
		program->setPositionValue(4,coordinate1->getY());
		program->setPositionValue(5,coordinate1->getZ());
		program->setPositionValue(6,coordinate1->getX());
		program->setPositionValue(7,coordinate1->getY());
		program->setPositionValue(8,coordinate1->getZ());
		program->drawPoints();
	}


}
Bottle::~Bottle(){

}
