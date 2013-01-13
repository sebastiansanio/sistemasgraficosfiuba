/*
 * CubeMapProgram.h
 *
 *  Created on: 28/01/2012
 *      Author: damian
 */

#ifndef CUBEMAPPROGRAM_H_
#define CUBEMAPPROGRAM_H_

#include "MainProgram.h"
#include "Light.h"
#include "BitMap.h"
#include "soil/SOIL.h"

class CubeMapProgram {

public:
	static CubeMapProgram* Instance();
	void setActualProgram();
	void setActualProgramFirstTime();
	void setTexture(int texId);
	void setLightPosition();
	void updateModelViewProjection();
	virtual ~CubeMapProgram();

protected:
	CubeMapProgram();
	CubeMapProgram(const CubeMapProgram & ) ;
	CubeMapProgram &operator= (const CubeMapProgram & ) ;

private:
	static CubeMapProgram* instance;
	MainProgram* program;
	int actualTexId;

	Light* lights[NUMLIGHT];
	float arrayBuffer[NUMLIGHT * 3];
};

#endif /* CUBEMAPPROGRAM_H_ */
