#ifndef BULLET_H_
#define BULLET_H_

#include "BasicProgram.h"
#include "TextureProgram.h"
#include "Curves/BSpline.h"
#include "BottleInstance.h"
#include <math.h>
#include "include/btBulletDynamicsCommon.h"
#include "include/btBulletCollisionCommon.h"
#include "RectangTex.h"


class Bullet{
public:
	static Bullet* Instance();
	void addPack();
	void drawBottles();
	Bullet();
	~Bullet();
	void advanceMotion();

private:
	RectangTex* rectangTex;
	btRigidBody* ramp;
	static Bullet* instance;
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btAlignedObjectArray<btRigidBody*>* bottles;


};

#endif
