#include "BottleInstance.h"
#include "Bottle.h"

BottleInstance::~BottleInstance(){

}
BottleInstance::BottleInstance(double initialDistance,double initialLiquidHeight,bool initialHasLabel){
	distance = initialDistance;
	liquidHeight = initialLiquidHeight;
	hasLabel = initialHasLabel;
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
double BottleInstance::getDistance(){
	return distance;
}
double BottleInstance::getLiquidHeight(){
	return liquidHeight;
}
bool BottleInstance::getHasLabel(){
	return hasLabel;
}

