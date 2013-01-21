#ifndef BULLET_H_
#define BULLET_H_

#include "BasicProgram.h"
#include "TextureProgram.h"
#include "Curves/BSpline.h"
#include "BottleInstance.h"
#include <math.h>

class Bullet{
public:
	Bullet();
	~Bullet();
	void advanceMotion();

private:
	vector<BottleInstance*>* bottles;
};

#endif
