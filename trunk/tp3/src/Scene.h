#ifndef Scene_H_
#define Scene_H_

#include "CubeRef.h"
#include "Rectang.h"
#include "RectangTex.h"
#include "Lampara.h"
#include "Bottle.h"
#include "AssemblyLine.h"
#include "BottleGenerator.h"
#include "BottleDispatcher.h"
#include "Bullet.h"

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
	BottleDispatcher* bottleDispatcher;
	Bullet* bullet;
};

#endif /* Scene_H_ */
