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

private:
	double distance;
	double liquidHeight;
	bool hasLabel;

};


#endif /* BOTTLEINSTANCE_H_ */
