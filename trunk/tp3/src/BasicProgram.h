/*
 * Program.h
 *
 *  Created on: 08/01/2012
 *      Author: damian
 */

#ifndef BASICPROGRAM_H_
#define BASICPROGRAM_H_

#include "MainProgram.h"
#include "Camera.h"

class BasicProgram {
public:
	static BasicProgram* Instance();
	void setActualProgram();
	void updateBuffer();
	void setPositionValue(int position, float value);
	void setColorValue(int position, float value);
	void setNormalValue(int position, float value);
	void updateModelViewProjection();
	void drawTriangle();
	virtual ~BasicProgram();

protected:
	BasicProgram();
	BasicProgram(const BasicProgram & ) ;
	BasicProgram &operator= (const BasicProgram & ) ;

private:
	static BasicProgram* instance;
	MainProgram* program;
	Attribute* positionAttrib;
	Attribute* colorAttrib;
	Attribute* normalAttrib;
};

#endif /* BASICPROGRAM_H_ */
