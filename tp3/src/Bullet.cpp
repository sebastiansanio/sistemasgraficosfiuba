#include "Bullet.h"
#include <iostream>


void Bullet::advanceMotion(){

	cout <<"advancing" <<endl;
}


Bullet::Bullet(){
	bottles = new vector<BottleInstance*>;
}

Bullet::~Bullet(){

}

