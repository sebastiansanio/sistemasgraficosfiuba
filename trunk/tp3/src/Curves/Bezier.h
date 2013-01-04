#ifndef BEZIER_H_
#define BEZIER_H_

#include <vector>
#include "Coordinate.h"

using namespace std;
class Bezier{
public:
	Bezier();
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

#endif /* BEZIER_H_ */
