/*
 * Scene.h
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#ifndef Scene_H_
#define Scene_H_

#include "CubeRef.h"
#include "Rectang.h"
#include "RectangTex.h"
#include "Lampara.h"
#include "Bottle.h"
#include "AssemblyLine.h"
#include "BottleGenerator.h"

class Scene {
public:
	static Scene* Instance();
	void printScene();
	virtual ~Scene();
	void advanceMotion();

protected:
	Scene();
	Scene(const Scene & ) ;
	Scene &operator= (const Scene & ) ;

private:
	int generateBottleTime;
	int generateBottleDelay;
	static Scene* instance;
	RectangTex* piso;
	RectangTex* pared;
	RectangTex* techo;
	CubeRef* cube1;
	Rectang* rectang;
	Lampara* lampara;
	Bottle* bottle;
	AssemblyLine* assemblyLine;
	BottleGenerator* bottleGenerator;
};

#endif /* Scene_H_ */
