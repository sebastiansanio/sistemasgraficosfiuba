/*
 * BottleProgram.h
 *
 *      Author: sebastian
 */

#ifndef ASSEMBLYLINEPROGRAM_H_
#define ASSEMBLYLINEPROGRAM_H_

#include "MainProgram.h"
#include "Light.h"
#include "BitMap.h"

class AssemblyLineProgram {

public:
	static AssemblyLineProgram* Instance();
	void setActualProgram();
	void setActualProgramFirstTime();
	void setTexture(int texId);
	void setLightPosition();
	void updateModelViewProjection();
	void setLiquidHeight(float height,bool hasLabel);

protected:
	AssemblyLineProgram();
	AssemblyLineProgram(const AssemblyLineProgram & ) ;
	AssemblyLineProgram &operator= (const AssemblyLineProgram & ) ;

private:
	static AssemblyLineProgram* instance;
	MainProgram* program;
	int actualTexId;

	Light* lights[NUMLIGHT];
	float arrayBuffer[NUMLIGHT * 3];
	float arrayBuffer2[NUMLIGHT * 3];
};

#endif /* ASSEMBLYLINEPROGRAM_H_ */
