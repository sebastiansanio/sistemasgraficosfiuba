#ifndef COORDINATE_H_
#define COORDINATE_H_

class Coordinate{
public:
	Coordinate(float x,float y,float z);
	~Coordinate();
	float getX();
	float getY();
	float getZ();
private:
	float x,y,z;
};



#endif /* COORDINATE_H_ */
