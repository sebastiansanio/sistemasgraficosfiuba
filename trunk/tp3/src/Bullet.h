#ifndef BULLET_H_
#define BULLET_H_

#include "BasicProgram.h"
#include "TextureProgram.h"
#include "Curves/BSpline.h"
#include "BottleInstance.h"
#include <math.h>

class Bullet{
public:
	static Bullet* Instance();
	void addPack();
	void drawBottles();
	Bullet();
	~Bullet();
	void advanceMotion();

private:
	static Bullet* instance;
	vector<BottleInstance*>* bottles;
};

#endif
