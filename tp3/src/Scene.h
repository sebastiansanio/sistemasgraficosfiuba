/*
 * Scene.h
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#ifndef Scene_H_
#define Scene_H_

#include "Cube.h"

class Scene {
public:
	static Scene* Instance();
	void printScene();
	virtual ~Scene();

protected:
	Scene();
	Scene(const Scene & ) ;
	Scene &operator= (const Scene & ) ;

private:
	static Scene* instance;
	Cube* cube;

};

#endif /* Scene_H_ */
