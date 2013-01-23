#ifndef BOTTLEINSTANCE_H_
#define BOTTLEINSTANCE_H_

#include <math.h>

class BottleInstance{
public:
	BottleInstance();
	~BottleInstance();
	BottleInstance(double initialDistance,double initialLiquidHeight,bool initialHasLabel);
	void setDistance(double newDistance);
	void setLiquidHeight(double newLiquidHeight);
	void setHasLabel(bool newHasLabel);
	void setLabelFinished(bool newLabelFinished);
	double getDistance();
	double getLiquidHeight();
	bool getHasLabel();
	bool getLabelFinished();
	bool isFilled();
	void setPosition(double newX,double newY,double newZ);
	double getX();
	double getY();
	double getZ();
	void setNormal(double newX,double newY,double newZ);
	double getNormalX();
	double getNormalY();
	double getNormalZ();

private:
	double distance;
	double liquidHeight;
	bool hasLabel;
	bool labelFinished;
	double posX;
	double posY;
	double posZ;
	double normalX;
	double normalY;
	double normalZ;

};


#endif /* BOTTLEINSTANCE_H_ */
