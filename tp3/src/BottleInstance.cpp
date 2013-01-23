#include "BottleInstance.h"
#include "Bottle.h"

BottleInstance::~BottleInstance(){

}

BottleInstance::BottleInstance(){

}

BottleInstance::BottleInstance(double initialDistance,double initialLiquidHeight,bool initialHasLabel){
	distance = initialDistance;
	liquidHeight = initialLiquidHeight;
	hasLabel = initialHasLabel;
	labelFinished = initialHasLabel;
}
bool BottleInstance::isFilled(){
	return (liquidHeight>=Bottle::Instance()->getFilledHeight());
}
void BottleInstance::setDistance(double newDistance){
	distance = newDistance;
}

void BottleInstance::setLiquidHeight(double newLiquidHeight){
	liquidHeight = newLiquidHeight;
}
void BottleInstance::setHasLabel(bool newHasLabel){
	hasLabel = newHasLabel;
}
void BottleInstance::setLabelFinished(bool newLabelFinished){
	labelFinished = newLabelFinished;
}
void BottleInstance::setFillFinished(bool newFillFinished){
	fillFinished = newFillFinished;
}
double BottleInstance::getDistance(){
	return distance;
}
double BottleInstance::getLiquidHeight(){
	return liquidHeight;
}
bool BottleInstance::getHasLabel(){
	return hasLabel;
}
bool BottleInstance::getLabelFinished(){
	return labelFinished;
}
bool BottleInstance::getFillFinished(){
	return fillFinished;
}
void BottleInstance::setPosition(double newX,double newY,double newZ){
	posX = newX;
	posY = newY;
	posZ = newZ;
}
double BottleInstance::getX(){
	return posX;
}
double BottleInstance::getY(){
	return posY;
}
double BottleInstance::getZ(){
	return posZ;
}
void BottleInstance::setNormal(double newX,double newY,double newZ){
	normalX = newX;
	normalY = newY;
	normalZ = newZ;
}
double BottleInstance::getNormalX(){
	return normalX;
}
double BottleInstance::getNormalY(){
	return normalY;
}
double BottleInstance::getNormalZ(){
	return normalZ;
}