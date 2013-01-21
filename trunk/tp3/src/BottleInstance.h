#ifndef BOTTLEINSTANCE_H_
#define BOTTLEINSTANCE_H_

#include <math.h>

class BottleInstance{
public:
	~BottleInstance();
	BottleInstance(double initialDistance,double initialLiquidHeight,bool initialHasLabel);
	void setDistance(double newDistance);
	void setLiquidHeight(double newLiquidHeight);
	void setHasLabel(bool newHasLabel);
	double getDistance();
	double getLiquidHeight();
	bool getHasLabel();
	bool isFilled();
	void setPosition(double newX,double newY,double newZ);
	double getX();
	double getY();
	double getZ();

private:
	double distance;
	double liquidHeight;
	bool hasLabel;
	double posX;
	double posY;
	double posZ;

};


#endif /* BOTTLEINSTANCE_H_ */
