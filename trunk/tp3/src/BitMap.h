#ifndef BITMAP_H_
#define BITMAP_H_
using namespace std;
#include <string.h>
#include <sstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

typedef struct {
  char bm[2];
  unsigned int tamano;//tamaño del archivo en total
  unsigned int reservado;
  unsigned int offset;//Donde empieza la información del bitmap
  unsigned int tamanoMetadatos;//tamaño del header del bitmap
  unsigned int altoEnPixels;
  unsigned int anchoEnPixels;
  short numeroPlanos;//no es importante para nosotros
  short profundidadColor;//debe ser 24
  unsigned int tipoCompresion;//debe ser 0
  unsigned int tamanoEstructura;//tamano de lo que seria la imagen
  unsigned int pixelPorMetroHorizontal;//no es importante para nosotros
  unsigned int pixelPorMetroVertical;//no es importante para nosotros
  unsigned int coloresUsados;//no es importante para nosotros
  unsigned int coloresImportantes;//no es importante para nosotros
} informacionDelBMP;

typedef struct{
   char r;
   char g;
   char b;
} colorType;

class BitMap {

private:
	informacionDelBMP* informacionImagen;
	bool seLevantoCorrectamente;
	unsigned long int bytesEnAncho,bytesEnAlto;
	unsigned char* data;

public:
	BitMap(string path);
	bool seLevantoBienElArchivo();
	bool esUnaImagenCorrecta();//Se refiere a: es un bmp, si es de profundidad 24 bits y si no tiene ningun tipo de compresion
	unsigned int getAncho();//lo devuelve en pixels
	unsigned int getAlto();//lo devuelve en pixels
	unsigned char* getMatriz();
	virtual ~BitMap();
};

#endif /* BITMAP_H_ */
