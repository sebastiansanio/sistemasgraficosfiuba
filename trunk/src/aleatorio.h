#ifndef ALEATORIO_H_
#define ALEATORIO_H_

#include <cstdlib>
#include <time.h>

class aleatorio{

	private:
		static int contador;

	public:
		aleatorio();
		static float obtener(float min,float max);

};


#endif
