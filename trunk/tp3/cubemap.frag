#version 400
#define NUMLIGHT 6

in vec3 Normal;
in vec3 Position;
in vec2 TexCoord;
in vec3 ReflectDir;

out vec4 FragColor;

uniform samplerCube Texture2;
uniform vec3 lightPos[NUMLIGHT];
uniform vec3 lightSpotDir[NUMLIGHT];

float rand(){
    return fract(sin(dot(Position ,vec3(12.9898,78.233,15.633))) * 43758.5453);
}

void main()
{	

	vec3 color = vec3(0.25,0.25,0.25) + vec3(0.64,0.4,0.32) * 0.25 * rand();
	
	color = mix(vec3(texture(Texture2,ReflectDir)),color,0.8);
	
	//Iluminacion ambiente
	
	float intAmbiente = 0.1;
	
	vec3 colorFinal = intAmbiente * color;
	
	
	for(int i = 0; i < NUMLIGHT ; i++){
	
		//Iluminacion difusa
	
		vec3 lightDir = normalize( lightPos[i] - Position );
		vec3 lightSpotDirection = normalize( lightSpotDir[i] - lightPos[i]);
		
		float intDifusa = dot(lightDir, Normal);
	
		//Si la cara esta del lado de la luz se aplica la iluminacion difusa y la especular
		if(intDifusa > 0.0) {
		
			//Si esta en el cono de la luz spot
			
			float angle = acos(dot(-lightDir, lightSpotDirection));
			float cutoff = radians( 90.0 );
			if( angle < cutoff ) {
				
				float spotFactor = pow(dot(-lightDir, lightSpotDirection),7);
				
				colorFinal += 0.5 * intDifusa * spotFactor * color;
				
				//Iluminacion especular
				
				//Vector de la posicion al ojo
				vec3 vista = normalize(vec3(-Position));
				
				vec3 h = normalize(vista + lightDir);
				
				colorFinal += vec3(0.5,0.5,0.5) * spotFactor * pow( max( dot(h,Normal), 0.0 ), 3.0);
					
			}
		}
	
	}
	
	FragColor = vec4( colorFinal, 1.0) ;
}