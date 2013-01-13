/*
 * Program.h
 *
 *  Created on: 08/01/2012
 *      Author: damian
 */

#ifndef BASICPROGRAM_H_
#define BASICPROGRAM_H_

#include "MainProgram.h"
#include "Light.h"

class BasicProgram {
public:
	static BasicProgram* Instance();
	void setActualProgram();
	void setActualProgramFirstTime();
	void setLightPosition();
	void updateModelViewProjection();
	virtual ~BasicProgram();

protected:
	BasicProgram();
	BasicProgram(const BasicProgram & ) ;
	BasicProgram &operator= (const BasicProgram & ) ;

//private:
	static BasicProgram* instance;
	MainProgram* program;
	Light* lights[NUMLIGHT];
	float arrayBuffer[NUMLIGHT * 3];
};

#endif /* BASICPROGRAM_H_ */
