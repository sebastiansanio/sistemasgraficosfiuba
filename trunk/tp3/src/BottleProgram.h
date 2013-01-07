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
	void updateBuffer();
	void setPositionValue(int position, float value);
	void setColorValue(int position, float value);
	void setNormalValue(int position, float value);
	void setTextureValue(int position, float value);
	void setTexture(int texId);
	void setLightPosition();
	void updateModelViewProjection();
	void drawTriangle();
	void setLiquidHeight(float height,bool hasLabel);
	virtual ~BottleProgram();

protected:
	BottleProgram();
	BottleProgram(const BottleProgram & ) ;
	BottleProgram &operator= (const BottleProgram & ) ;

private:
	static BottleProgram* instance;
	MainProgram* program;
	Attribute* positionAttrib;
	Attribute* colorAttrib;
	Attribute* normalAttrib;
	Attribute* textureAttrib;
	int actualTexId;

	Light* lights[NUMLIGHT];
	float arrayBuffer[NUMLIGHT * 3];
	float arrayBuffer2[NUMLIGHT * 3];
	float arrayBufferLiquid[3];
};

#endif /* BOTTLEPROGRAM_H_ */
