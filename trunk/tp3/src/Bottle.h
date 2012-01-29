#ifndef BOTTLE_H_
#define BOTTLE_H_

#include "BasicProgram.h"
#include "TextureProgram.h"
#include "Curves/Bezier.h"

class Bottle{
public:
	Bottle();
	~Bottle();
	void print();

private:
	TextureProgram* program;
};




#endif /* BOTTLE_H_ */
