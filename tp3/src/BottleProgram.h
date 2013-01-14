/*
 * BottleProgram.h
 *
 *      Author: sebastian
 */

#ifndef BOTTLEPROGRAM_H_
#define BOTTLEPROGRAM_H_

#include "MainProgram.h"
#include "Light.h"
#include "BitMap.h"

class BottleProgram {

public:
	static BottleProgram* Instance();
	void setActualProgram();
	void setActualProgramFirstTime();
	void setTexture(int texId);
	void setLightPosition();
	void updateModelViewProjection();
	void setLiquidHeight(float height,bool hasLabel);
	virtual ~BottleProgram();

protected:
	BottleProgram();
	BottleProgram(const BottleProgram & ) ;
	BottleProgram &operator= (const BottleProgram & ) ;

private:
	static BottleProgram* instance;
	MainProgram* program;
	int actualTexId;

	Light* lights[NUMLIGHT];
	float arrayBuffer[NUMLIGHT * 3];
	float arrayBuffer2[NUMLIGHT * 3];
	float arrayBufferLiquid[3];
};

#endif /* BOTTLEPROGRAM_H_ */
