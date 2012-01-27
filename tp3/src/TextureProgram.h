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
	void updateBuffer();
	void setPositionValue(int position, float value);
	void setColorValue(int position, float value);
	void setNormalValue(int position, float value);
	void setTextureValue(int position, float value);
	void setTexture(int texId);
	void updateModelViewProjection();
	void drawTriangle();
	virtual ~TextureProgram();

protected:
	TextureProgram();
	TextureProgram(const TextureProgram & ) ;
	TextureProgram &operator= (const TextureProgram & ) ;

private:
	static TextureProgram* instance;
	void setLightPosition();
	MainProgram* program;
	Attribute* positionAttrib;
	Attribute* colorAttrib;
	Attribute* normalAttrib;
	Attribute* textureAttrib;
	int actualTexId;

	Light* lights[NUMLIGHT];
	float arrayBuffer[NUMLIGHT * 3];
};

#endif /* TEXTUREPROGRAM_H_ */
