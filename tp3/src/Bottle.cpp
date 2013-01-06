#include "Bottle.h"
#define PI 3.14159265

Bottle::Bottle(){
	program = TextureProgram::Instance();
	bezier=new Bezier();
	bezier->addPoint(0,0,0);
	bezier->addPoint(0,0.3,0);
	bezier->addPoint(0,0.3,0.1);
	bezier->addPoint(0,0.3,0.4);
	bezier->addPoint(0,0.27,0.6);
	bezier->addPoint(0,0.3,0.8);
	bezier->addPoint(0,0.3,1.0);
	bezier->addPoint(0,0.35,1.1);
	bezier->addPoint(0,0.1,1.4);
	bezier->addPoint(0,0.07,1.6);
	bezier->calculate();
}
void Bottle::print(){
	program->setTexture(2);
	program->setActualProgram();
	program->updateModelViewProjection();


	vector<Coordinate*>* points= bezier->getPoints();
	float step = 10;
	unsigned int size = points->size();

	float ySize = points->at(size-1)->getZ() - points->at(0)->getZ();

	float labelXSize = 180;
	float labelYSize = ySize;

	for(unsigned int i=0;i<size-1;i++){
		for(float j=0;j<360;j=j+step){
			program->setPositionValue(0,points->at(i)->getY()*cos(PI*j/180));
			program->setPositionValue(1,points->at(i)->getY()*sin(PI*j/180));
			program->setPositionValue(2,points->at(i)->getZ());
			program->setPositionValue(3,points->at(i)->getY()*cos(PI*(j+step)/180));
			program->setPositionValue(4,points->at(i)->getY()*sin(PI*(j+step)/180));
			program->setPositionValue(5,points->at(i)->getZ());
			program->setPositionValue(6,points->at(i+1)->getY()*cos(PI*j/180));
			program->setPositionValue(7,points->at(i+1)->getY()*sin(PI*j/180));
			program->setPositionValue(8,points->at(i+1)->getZ());
			program->setTextureValue(0,j/labelXSize);
			program->setTextureValue(1,1-points->at(i)->getZ()/labelYSize);
			program->setTextureValue(2,(j+step)/labelXSize);
			program->setTextureValue(3,1-points->at(i)->getZ()/labelYSize);
			program->setTextureValue(4,j/labelXSize);
			program->setTextureValue(5,1-points->at(i+1)->getZ()/labelYSize);
			program->drawTriangle();

			program->setPositionValue(0,points->at(i+1)->getY()*cos(PI*(j+step)/180));
			program->setPositionValue(1,points->at(i+1)->getY()*sin(PI*(j+step)/180));
			program->setPositionValue(2,points->at(i+1)->getZ());
			program->setTextureValue(0,(j+step)/labelXSize);
			program->setTextureValue(1,1-points->at(i+1)->getZ()/labelYSize);
			program->drawTriangle();
		}

	}

}
Bottle::~Bottle(){

}
