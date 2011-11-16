#version 400

#define PI 3.14159265

in vec3 VertexPosition;
in vec3 VertexNormal;
in vec3 VertexColor;
in vec3 VertexNorm;
in vec2 VertexTexture;

out vec3 Color;
out vec3 Position;
out vec3 Normal;

uniform mat4 ModelMatrix;

uniform mat4 RotationMatrix;

uniform int opcion;
uniform int opcionshader;

uniform float DoblarXEje;
uniform float DoblarAngulo;

uniform float RetorcerAng;

uniform float RuidoAmplitud;
uniform float RuidoInvLongOnda;
uniform float RuidoFase;

uniform float EsfRadio;
uniform float EsfFactor;

out vec2 TexCoord;
out vec3 ReflectDir;

void main()
{
	TexCoord = VertexTexture;

	Color = VertexColor;
	
	vec3 posicion = vec3(ModelMatrix * vec4(VertexPosition,1.0));
	vec3 normal = vec3(ModelMatrix * vec4(VertexNormal,0.0));

	float x = posicion.x;
	float y = posicion.y;
	float z = posicion.z;

	float xNorm = normal.x;
	float yNorm = normal.y;
	float zNorm = normal.z;

	if(opcion == 1){
		//Doblar
		float xEje = DoblarXEje;
		float angulo = DoblarAngulo;

		//El angulo varia segun la altura

		angulo = angulo * y;
	
		x = x + xEje;

		float xMod = cos(angulo) * x - sin(angulo) * y;
		float yMod = sin(angulo) * x + cos(angulo) * y;

		x = xMod;
		y = yMod;

		x = x - xEje;

		xNorm = xNorm + xEje;

		xMod = cos(angulo) * xNorm - sin(angulo) * yNorm;
		yMod = sin(angulo) * xNorm + cos(angulo) * yNorm;

		xNorm = xMod;
		yNorm = yMod;

		xNorm = xNorm - xEje;
	} else if(opcion == 2){
		//Retorcer
		//El angulo es lo que retuerce en un 1.0 de la pantalla
		float angRet = RetorcerAng;

		angRet = angRet * y;

		float xMod = cos(angRet) * x + sin(angRet) * z;
		float zMod = - sin(angRet) * x + cos(angRet) * z;

		x = xMod;
		z = zMod;

		float xNormMod = cos(angRet) * xNorm + sin(angRet) * zNorm;
		float zNormMod = - sin(angRet) * xNorm + cos(angRet) * zNorm;

		xNorm = xNormMod;
		zNorm = zNormMod;
	} else if(opcion == 3){
		//Ruido
		float amplitud = RuidoAmplitud;
		float invLongOnda = RuidoInvLongOnda;

		y = y + amplitud * sin((x+RuidoFase)*invLongOnda) + amplitud * sin((z+RuidoFase)*invLongOnda);

		x = x + amplitud * sin((y+RuidoFase)*invLongOnda) + amplitud * sin((z+RuidoFase)*invLongOnda);

		z = z + amplitud * sin((x+RuidoFase)*invLongOnda) + amplitud * sin((y+RuidoFase)*invLongOnda);

		//Para mejorar el efecto de la sombra
		amplitud = amplitud * 2;

		yNorm = yNorm + amplitud * sin((xNorm+RuidoFase)*invLongOnda) + amplitud * sin((zNorm+RuidoFase)*invLongOnda);

		xNorm = xNorm + amplitud * sin((yNorm+RuidoFase)*invLongOnda) + amplitud * sin((zNorm+RuidoFase)*invLongOnda);

		zNorm = zNorm + amplitud * sin((xNorm+RuidoFase)*invLongOnda) + amplitud * sin((yNorm+RuidoFase)*invLongOnda);
	} else if (opcion == 4){
		//Esferizar
		float radio = EsfRadio;
		float factorEsf = EsfFactor;

		float modPunto = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
	
		float difXEsf = (x / modPunto * radio) - x;

		float difYEsf = (y / modPunto * radio) - y;

		float difZEsf = (z / modPunto * radio) - z;

		x = x + factorEsf * difXEsf;

		y = y + factorEsf * difYEsf;

		z = z + factorEsf * difZEsf;

		xNorm = xNorm + factorEsf * (x + difXEsf);
		yNorm = yNorm + factorEsf * (y + difYEsf);
		zNorm = zNorm + factorEsf * (z + difZEsf);

		factorEsf = factorEsf + 0.25;

		if(factorEsf>=1.0){
			factorEsf=1.0;
		}

		xNorm = xNorm + factorEsf * (x - xNorm);
		yNorm = yNorm + factorEsf * (y - yNorm);
		zNorm = zNorm + factorEsf * (z - zNorm);
	}

	posicion = vec3( RotationMatrix * vec4(x,y,z,1.0));
	normal = vec3( RotationMatrix * vec4(xNorm,yNorm,zNorm,0.0));

	Normal = normalize(normal);
	Position = vec3(posicion);

	vec3 NormalMundo = normal;
	vec3 PositionMundo = posicion;
	vec3 VistaMundo = normalize( vec3(0.0,0.0,-1.0) - PositionMundo );
	ReflectDir = reflect(-VistaMundo, NormalMundo);

	if(opcionshader != 4){
		posicion = vec3((posicion.x)+0.40,posicion.y,posicion.z);
	}

	gl_Position = vec4(posicion,1.0);
}