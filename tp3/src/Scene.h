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
#include "Bottle.h"
#include "AssemblyLine.h"

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
	RectangTex* piso;
	RectangTex* pared;
	CubeRef* cube1;
	Rectang* rectang;
	Bottle* bottle;
	AssemblyLine* assemblyLine;
};

#endif /* Scene_H_ */
