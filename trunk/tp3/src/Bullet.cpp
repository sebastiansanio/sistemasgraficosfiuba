#include "Bullet.h"
#include <iostream>
#include "Bottle.h"
#include "Curves/Coordinate.h"
#include "Ramp.h"
#include <math.h>

Bullet* Bullet::instance = 0;
Bullet* Bullet::Instance ()
{
  if (instance == 0)
  {
    instance = new Bullet();
  }
  return instance;
}

Bullet::Bullet(){

	bottles = new btAlignedObjectArray<btRigidBody*>();
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,0,-10));

    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,0,1),0);
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);

    dynamicsWorld->addRigidBody(groundRigidBody);


	addPack();
}

Bullet::~Bullet(){

	delete dynamicsWorld;
	delete solver;
	delete broadphase;
	delete dispatcher;
	delete collisionConfiguration;
}

void Bullet::addPack(){

//	BottleInstance* bottle = new BottleInstance();
//	bottle->setPosition(11.2,3.9,3.7);
//	bottle->setNormal(0,0,1);
//	bottles->push_back(bottle);

	btBoxShape* collisionShape = new btBoxShape(btVector3(0.3,0.3,0.5));
	btVector3 fallInertia(0,0,0);
	btScalar mass = 1;
	collisionShape->calculateLocalInertia(mass,fallInertia);
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(btScalar(0),btScalar(0),btScalar(3.7)));
	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass,motionState,collisionShape,fallInertia);
    btRigidBody* rigidBody = new btRigidBody(rigidBodyCI);
    bottles->push_back(rigidBody);
    dynamicsWorld->addRigidBody(rigidBody);

}

void Bullet::drawBottles(){

	for(int i = 0;i<bottles->size();i++){
		glPushMatrix();
			btTransform transform;

			btRigidBody* rigidBody = bottles->at(i);
		    rigidBody->getMotionState()->getWorldTransform(transform);

		    glTranslatef(transform.getOrigin().getX(),transform.getOrigin().getY(),transform.getOrigin().getZ());
		    btVector3 axis = transform.getRotation().getAxis();
		    glRotatef(transform.getRotation().getAngle()*360/6.2832f,axis.getX(),axis.getY(),axis.getZ());
		    Bottle::Instance()->printPack();

		glPopMatrix();
	}

}

void Bullet::advanceMotion(){
	dynamicsWorld->stepSimulation(1/60.f,10);

}

