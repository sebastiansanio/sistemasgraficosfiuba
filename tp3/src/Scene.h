/*
 * Scene.h
 *
 *  Created on: 10/01/2012
 *      Author: damian
 */

#ifndef Scene_H_
#define Scene_H_

#include "CubeTex.h"
#include "Rectang.h"
#include "RectangTex.h"

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
	CubeTex* cube1;

};

#endif /* Scene_H_ */
