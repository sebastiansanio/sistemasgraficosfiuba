#ifndef COORDINATE_H_
#define COORDINATE_H_

class Coordinate{
public:
	Coordinate(float x,float y,float z);
	~Coordinate();
	void normalize();
	float getX();
	float getY();
	float getZ();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
private:
	float x,y,z;
};



#endif /* COORDINATE_H_ */
