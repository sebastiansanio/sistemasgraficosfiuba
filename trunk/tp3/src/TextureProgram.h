/*
 * TextureProgram.h
 *
 *  Created on: 24/01/2012
 *      Author: damian
 */

#ifndef TEXTUREPROGRAM_H_
#define TEXTUREPROGRAM_H_

#include "MainProgram.h"
#include "Light.h"
#include "BitMap.h"

class TextureProgram {

public:
	static TextureProgram* Instance();
	void setActualProgram();
	void setActualProgramFirstTime();
	void setTexture(int texId);
	void setLightPosition();
	void updateModelViewProjection();
	virtual ~TextureProgram();

protected:
	TextureProgram();
	TextureProgram(const TextureProgram & ) ;
	TextureProgram &operator= (const TextureProgram & ) ;

private:
	static TextureProgram* instance;
	MainProgram* program;
	int actualTexId;

	Light* lights[NUMLIGHT];
	float arrayBuffer[NUMLIGHT * 3];
};

#endif /* TEXTUREPROGRAM_H_ */
