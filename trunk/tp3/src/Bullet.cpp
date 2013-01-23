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
	bottles = new vector<BottleInstance*>;

    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-10,0));
    groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
    btCollisionShape* fallShape = new btSphereShape(1);


    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
    btRigidBody::btRigidBodyConstructionInfo
            groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);


    btDefaultMotionState* fallMotionState =
            new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
    btScalar mass = 1;
    btVector3 fallInertia(0,0,0);
    fallShape->calculateLocalInertia(mass,fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
    btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
    dynamicsWorld->addRigidBody(fallRigidBody);


    for (int i=0 ; i<300 ; i++) {
            dynamicsWorld->stepSimulation(1/60.f,10);

            btTransform trans;
            fallRigidBody->getMotionState()->getWorldTransform(trans);

//            std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
    }

    dynamicsWorld->removeRigidBody(fallRigidBody);
    delete fallRigidBody->getMotionState();
    delete fallRigidBody;

    dynamicsWorld->removeRigidBody(groundRigidBody);
    delete groundRigidBody->getMotionState();
    delete groundRigidBody;


    delete fallShape;

    delete groundShape;


    delete dynamicsWorld;
    delete solver;
    delete collisionConfiguration;
    delete dispatcher;
    delete broadphase;





	addPack();
}

Bullet::~Bullet(){

}

void Bullet::addPack(){
	BottleInstance* bottle = new BottleInstance();
	Coordinate* normal = Ramp::Instance()->getNormal();

	bottle->setPosition(11.2,3.9,3.7);
	bottle->setNormal(normal->getX(),normal->getY(),normal->getZ());

	cout << normal->getX() << ":" <<normal->getY()<<":"<<normal->getZ() <<endl;

	bottles->push_back(bottle);

}

void Bullet::drawBottles(){

	for(unsigned int i = 0;i<bottles->size();i++){
		glPushMatrix();
			glTranslatef(bottles->at(i)->getX(),bottles->at(i)->getY(),bottles->at(i)->getZ());
			Bottle::Instance()->printPack();
		glPopMatrix();
	}

}

void Bullet::advanceMotion(){


}

