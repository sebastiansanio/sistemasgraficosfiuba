#include "BitMap.h"

BitMap::BitMap(string path) {

	this->informacionImagen=new informacionDelBMP;
    // referencia al archivo
    fstream  archivo;

    //intenta abrir el archivo en modo lectura y binario
    archivo.open(path.c_str(), fstream::in | fstream::binary );

    //verifico la apertura del mismo
    this->seLevantoCorrectamente=archivo.is_open();
    if (!this->seLevantoCorrectamente) {
        archivo.close();
    }else{
			//la primera parte del archivo son los datos del bitmap, los cargo en la estructura
			archivo.read((char *)&(this->informacionImagen->bm),2);
			archivo.read((char *)&(this->informacionImagen->tamano),sizeof(this->informacionImagen->tamano));
			archivo.read((char *)&(this->informacionImagen->reservado),sizeof(this->informacionImagen->reservado));
			archivo.read((char *)&(this->informacionImagen->offset),sizeof(this->informacionImagen->offset));
			archivo.read((char *)&(this->informacionImagen->tamanoMetadatos),sizeof(this->informacionImagen->tamanoMetadatos));
			archivo.read((char *)&(this->informacionImagen->anchoEnPixels),sizeof(this->informacionImagen->anchoEnPixels));
			this->bytesEnAncho=this->informacionImagen->anchoEnPixels*3;
			archivo.read((char *)&(this->informacionImagen->altoEnPixels),sizeof(this->informacionImagen->altoEnPixels));
			this->bytesEnAlto=this->informacionImagen->altoEnPixels*3;
			archivo.read((char *)&(this->informacionImagen->numeroPlanos),sizeof(this->informacionImagen->numeroPlanos));
			archivo.read((char *)&(this->informacionImagen->profundidadColor),sizeof(this->informacionImagen->profundidadColor));
			archivo.read((char *)&(this->informacionImagen->tipoCompresion),sizeof(this->informacionImagen->tipoCompresion));
			archivo.read((char *)&(this->informacionImagen->tamanoEstructura),sizeof(this->informacionImagen->tamanoEstructura));
			archivo.read((char *)&(this->informacionImagen->pixelPorMetroHorizontal),sizeof(this->informacionImagen->pixelPorMetroHorizontal));
			archivo.read((char *)&(this->informacionImagen->pixelPorMetroVertical),sizeof(this->informacionImagen->pixelPorMetroVertical));
			archivo.read((char *)&(this->informacionImagen->coloresUsados),sizeof(this->informacionImagen->coloresUsados));
			archivo.read((char *)&(this->informacionImagen->coloresImportantes),sizeof(this->informacionImagen->coloresImportantes));

			if(this->esUnaImagenCorrecta()){
		    	colorType** matrizDePixeles=new colorType*[this->informacionImagen->altoEnPixels];
		    	for(unsigned int i=0;i<this->informacionImagen->altoEnPixels;i++){
		    		matrizDePixeles[i]=new colorType[this->informacionImagen->anchoEnPixels];
		    	}

		    //Corroboro los bytes de relleno
		    	int resto = this->informacionImagen->anchoEnPixels % 4;

				//Paso la informacion del archivo a la matriz
				for(unsigned int i=0;i<this->informacionImagen->altoEnPixels;i++){
					for(unsigned int j=0; j<this->informacionImagen->anchoEnPixels;j++){
						char color[3]=" ";
						char rojo,verde,azul;
						archivo.read((char*)&color,3);
						rojo = color[2];
						verde = color[1];
						azul = color[0];
						//Corroboro que el color no sea 0 255 0, que es lo que usamos para transparencia
						//Por ahora si la imagen tiene el color de la transprencia lo deja así
						matrizDePixeles[this->informacionImagen->altoEnPixels -1 - i][j].r=rojo;
						matrizDePixeles[this->informacionImagen->altoEnPixels -1 - i][j].g=verde;
						matrizDePixeles[this->informacionImagen->altoEnPixels -1 - i][j].b=azul;
					}
					//Quito los bytes de relleno
					for(int i=0;i<resto;i++){
						char bytes;
						archivo.read(&bytes,1);
					}
				}
				archivo.close();

				this->data = new unsigned char[this->informacionImagen->altoEnPixels * this->informacionImagen->anchoEnPixels * 3];

				int counter=0;

				for(unsigned int i=0;i<this->informacionImagen->altoEnPixels;i++){
					for(unsigned int j=0; j<this->informacionImagen->anchoEnPixels;j++){
						this->data[counter++]=matrizDePixeles[i][j].r;
						this->data[counter++]=matrizDePixeles[i][j].g;
						this->data[counter++]=matrizDePixeles[i][j].b;
					}
				}

				for(unsigned int i=0;i<this->informacionImagen->altoEnPixels;i++){
					delete [] matrizDePixeles[i];
				}
				delete [] matrizDePixeles;
			}
    }
}

bool BitMap::seLevantoBienElArchivo(){
	return this->seLevantoCorrectamente;
}

bool BitMap::esUnaImagenCorrecta(){
	return ((this->seLevantoBienElArchivo())and(this->informacionImagen->profundidadColor==24)and(this->informacionImagen->bm[0]=='B')and(this->informacionImagen->bm[1]=='M')and(this->informacionImagen->tamanoEstructura>0)and(this->informacionImagen->tipoCompresion==0));
}

unsigned char* BitMap::getMatriz(){
	return this->data;
}

unsigned int BitMap::getAlto(){
	return this->informacionImagen->altoEnPixels;
}

unsigned int BitMap::getAncho(){
	return this->informacionImagen->anchoEnPixels;
}
BitMap::~BitMap() {
	delete [] this->data;
	delete this->informacionImagen;
}
