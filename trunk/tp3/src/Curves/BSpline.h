#ifndef BSPLINE_H_
#define BSPLINE_H_

#include <vector>
#include "Coordinate.h"

using namespace std;
class BSpline{
public:
	BSpline();
	void addPoint(float x, float y,float z);
	void calculate();
	bool isEmpty();
	Coordinate* getPoint();
	void eraseAll();
	vector<Coordinate*>* getPoints();
	~Bezier();
private:
	vector<Coordinate*>* controlPoints;
	vector<Coordinate*>* curvePoints;
};

#endif /* BSPLINE_H_ */
