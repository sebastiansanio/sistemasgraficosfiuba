#include "aleatorio.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int aleatorio::contador=0;

aleatorio::aleatorio(){
	srand(time(NULL));
}

float aleatorio::obtener(float min,float max){
	contador++;
	//srand((time(NULL)+1)*(1+contador));
	float aleat;
	aleat = ((float) (rand())) / (float) RAND_MAX;
	aleat = min + (max-min)*aleat;
	return aleat;
}

