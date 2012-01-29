#include "Bottle.h"

Bottle::Bottle(){
	program = TextureProgram::Instance();




}


Bottle::~Bottle(){



}

void Bottle::print(){
	program->setTexture(1);
	program->setActualProgram();

	vector<float>* points=new vector<float>();
	points->push_back(0.5);

	//for(float i=0;i+=0.1;i<)


	program->updateModelViewProjection();
	program->setPositionValue(0,1.0);
	program->setPositionValue(1,1.0);
	program->setPositionValue(2,1.0);
	program->setPositionValue(3,1.0);
	program->setPositionValue(4,4.0);
	program->setPositionValue(5,1.0);
	program->setPositionValue(6,1.0);
	program->setPositionValue(7,1.0);
	program->setPositionValue(8,4.0);
	program->drawTriangle();
}
