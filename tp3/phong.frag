#version 130

in vec3 Color;
in vec3 Normal;
in vec3 Position;

out vec4 FragColor;

uniform vec3 lightPos[1];

void main()
{

	//Iluminacion ambiente
	
	float intAmbiente = 0.2;
	
	vec3 colorFinal = intAmbiente * Color;
	
	//Iluminacion difusa
	
	vec3 lightDir = normalize( lightPos[0] - Position );
	
	float intDifusa = dot(lightDir, Normal);
	
	//Si la cara esta del lado de la luz se aplica la iluminacion difusa y la especular
	if(intDifusa > 0.0) {
		
		colorFinal += intDifusa * Color;
		
		//Iluminacion especular
		
		//Vector de la posicion al ojo
		vec3 vista = normalize(vec3(-Position));
		
		vec3 h = normalize(vista + lightDir);
		
		colorFinal += vec3(0.8,0.8,0.8) * pow( max( dot(h,Normal), 0.0 ), 5.0);
		
		//colorFinal = vec3(0.0,0.0,dot(Normal,lightDir));
	
	}
	
	FragColor = vec4( colorFinal, 1.0) ;
}