#version 400
#define NUMLIGHT 2

in vec3 Color;
in vec3 Normal;
in vec3 Position;

out vec4 FragColor;

uniform vec3 lightPos[NUMLIGHT];
uniform vec3 lightSpotDir[NUMLIGHT];

void main()
{

	//Iluminacion ambiente
	
	float intAmbiente = 0.1;
	
	vec3 colorFinal = intAmbiente * Color;
	
	
	for(int i = 0; i < NUMLIGHT ; i++){
	
		//Iluminacion difusa
	
		vec3 lightDir = normalize( lightPos[i] - Position );
		vec3 lightSpotDirection = normalize( lightSpotDir[i] - lightPos[i]);
		
		float intDifusa = dot(lightDir, Normal);
	
		//Si la cara esta del lado de la luz se aplica la iluminacion difusa y la especular
		if(intDifusa > 0.0) {
		
			//Si esta en el cono de la luz spot
			
			float angle = acos(dot(-lightDir, lightSpotDirection));
			float cutoff = radians( 40.0 );
			if( angle < cutoff ) {
				
				float spotFactor = 0.8 * pow(dot(-lightDir, lightSpotDirection),8);
				
				colorFinal += 0.7 * intDifusa * spotFactor * Color;
				
				//Iluminacion especular
				
				//Vector de la posicion al ojo
				vec3 vista = normalize(vec3(-Position));
				
				vec3 h = normalize(vista + lightDir);
				
				colorFinal += vec3(0.5,0.5,0.5) * spotFactor * pow( max( dot(h,Normal), 0.0 ), 2.0);
					
			}
		}
	
	}
	
	FragColor = vec4( colorFinal, 1.0) ;
}