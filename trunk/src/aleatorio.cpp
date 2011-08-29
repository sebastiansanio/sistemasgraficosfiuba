#include "aleatorio.h"
#include <stdio.h>
aleatorio::aleatorio(){
	srand(time(NULL));
}

float aleatorio::obtener(float min,float max){
	float aleat;
	aleat = ((float) (rand())) / (float) RAND_MAX;
	aleat = min + (max-min)*aleat;
	srand((time(NULL)+1)*(1+contador));
	return aleat;
}

