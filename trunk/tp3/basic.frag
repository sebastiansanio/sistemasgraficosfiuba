#version 400

in vec3 Color;
in vec3 Normal;
in vec3 Position;

out vec4 FragColor;

uniform vec3 lightPos[1];

void main()
{
	float intAmbiente = 0.2;
	
	vec3 s = normalize( lightPos[0] - Position );
	
	float intDifusa = max( dot(s, Normal), 0.0 );
	
	vec3 colorFinal = ( intAmbiente + intDifusa ) * Color;
	
	//Iluminacion especular
	
	//Vector de la posicion al ojo
	vec3 vista = normalize(vec3(-Position));
	
	vec3 h = normalize(s + vista);
	
	colorFinal += vec3(1.0,1.0,1.0) * pow( max( dot(h,Normal), 0.0 ), 3.0);
	
	FragColor = vec4( colorFinal, 1.0) ;
}