/*
 * Program.h
 *
 *  Created on: 08/01/2012
 *      Author: damian
 */

#ifndef BASICPROGRAM_H_
#define BASICPROGRAM_H_

#include "MainProgram.h"

class BasicProgram {
public:
	BasicProgram();
	void setActualProgram();
	void updateBuffer();
	void setPositionValue(int position, float value);
	void setColorValue(int position, float value);
	void drawTriangle();
	virtual ~BasicProgram();


private:
	MainProgram* program;
	Attribute* positionAttrib;
	Attribute* colorAttrib;
};

#endif /* BASICPROGRAM_H_ */
