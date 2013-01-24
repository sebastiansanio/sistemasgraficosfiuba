#include "Bullet.h"
#include <iostream>
#include "Bottle.h"
#include "Curves/Coordinate.h"
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


    btCollisionShape* wallShape1 = new btStaticPlaneShape(btVector3(0,1,0),0);
    btDefaultMotionState* wallMotionState1 = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-13,0)));
    btRigidBody::btRigidBodyConstructionInfo wallRigidBodyCI1(0,wallMotionState1,wallShape1,btVector3(0,0,0));
    btRigidBody* wallRigidBody1 = new btRigidBody(wallRigidBodyCI1);
    dynamicsWorld->addRigidBody(wallRigidBody1);

    btCollisionShape* wallShape2 = new btStaticPlaneShape(btVector3(0,-1,0),0);
    btDefaultMotionState* wallMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,20,0)));
    btRigidBody::btRigidBodyConstructionInfo wallRigidBodyCI2(0,wallMotionState2,wallShape2,btVector3(0,0,0));
    btRigidBody* wallRigidBody2 = new btRigidBody(wallRigidBodyCI2);
    dynamicsWorld->addRigidBody(wallRigidBody2);

    btCollisionShape* wallShape3 = new btStaticPlaneShape(btVector3(1,0,0),0);
    btDefaultMotionState* wallMotionState3 = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(-20,0,0)));
    btRigidBody::btRigidBodyConstructionInfo wallRigidBodyCI3(0,wallMotionState3,wallShape3,btVector3(0,0,0));
    btRigidBody* wallRigidBody3 = new btRigidBody(wallRigidBodyCI3);
    dynamicsWorld->addRigidBody(wallRigidBody3);

    btCollisionShape* wallShape4 = new btStaticPlaneShape(btVector3(-1,0,0),0);
    btDefaultMotionState* wallMotionState4 = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(20,0,0)));
    btRigidBody::btRigidBodyConstructionInfo wallRigidBodyCI4(0,wallMotionState4,wallShape4,btVector3(0,0,0));
    btRigidBody* wallRigidBody4 = new btRigidBody(wallRigidBodyCI4);
    dynamicsWorld->addRigidBody(wallRigidBody4);

    rectangTex = new RectangTex(0.50,3.5,2,1);
    btCollisionShape* rampShape = new btBoxShape(btVector3(0.50,3.5,0.001));
    float mass = 0;
    btVector3 fallInertia(0,0,0);
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(btScalar(11.25),btScalar(1.1),btScalar(1.8)));
    transform.setRotation(btQuaternion(btVector3(1,0,0),btScalar(25*6.28318531/360)));
    btDefaultMotionState* motionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass,motionState,rampShape,fallInertia);
    ramp = new btRigidBody(rigidBodyCI);
    dynamicsWorld->addRigidBody(ramp);


}

Bullet::~Bullet(){

	delete dynamicsWorld;
	delete solver;
	delete broadphase;
	delete dispatcher;
	delete collisionConfiguration;
}

void Bullet::addPack(){

	btBoxShape* collisionShape = new btBoxShape(btVector3(0.3,0.3,0.5));
	btVector3 fallInertia(0,0,0);
	btScalar mass = 0.2;
	collisionShape->calculateLocalInertia(mass,fallInertia);
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(btScalar(11.25),btScalar(4.3),btScalar(3.8)));
	transform.setRotation(btQuaternion(btVector3(1,0,0),btScalar(25*6.28318531/360)));
	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass,motionState,collisionShape,fallInertia);
    btRigidBody* rigidBody = new btRigidBody(rigidBodyCI);
    rigidBody->applyCentralImpulse(btVector3(0,-3,-1));
    bottles->push_back(rigidBody);
    dynamicsWorld->addRigidBody(rigidBody);

}

void Bullet::drawBottles(){

	glPushMatrix();
		btTransform transformRamp;
		ramp->getMotionState()->getWorldTransform(transformRamp);
		glTranslatef(transformRamp.getOrigin().getX(),transformRamp.getOrigin().getY(),transformRamp.getOrigin().getZ());
		btVector3 axis = transformRamp.getRotation().getAxis();
		glRotatef(transformRamp.getRotation().getAngle()*360/6.2832f,axis.getX(),axis.getY(),axis.getZ());
		rectangTex->print();
	glPopMatrix();

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

