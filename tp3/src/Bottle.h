#ifndef BOTTLE_H_
#define BOTTLE_H_

#include "BasicProgram.h"
#include "TextureProgram.h"
#include "Curves/Bezier.h"
#include <math.h>

class Bottle{
public:
	Bottle();
	~Bottle();
	void print();

private:
	BasicProgram* program;
	Bezier* bezier;
};




#endif /* BOTTLE_H_ */
