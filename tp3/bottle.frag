#version 130
#define NUMLIGHT 6

in vec3 Normal;
in vec3 Position;
in vec2 TexCoord;
in float height;

out vec4 FragColor;

uniform sampler2D Texture1;

uniform vec3 liquidHeight;
uniform vec3 lightPosition[NUMLIGHT];
uniform vec3 lightSpotDirect[NUMLIGHT];

void main()
{
	vec3 color = vec3(texture( Texture1, TexCoord ));
	
	
	float intAmbiente = 0.2;
	float alpha = 1;
	float currentLiquidHeight = liquidHeight[0];
	float hasLabel = liquidHeight[1];
	 
	if((color[0] == 0 && color[1] == 0 && color[2] == 0) || hasLabel == 0 ){
		if(height< currentLiquidHeight){
			color[0] = 0.4; 
			color[1] = 0.25;
			color[2] = 0.23;

		}else{
			color[0] = 1.0; 
			color[1] = 1.0;
			color[2] = 1.0;
			alpha = 0.4;		
		}	
	}
	
	vec3 colorFinal = intAmbiente * color;
	
	
	for(int i = 0; i < NUMLIGHT ; i++){
	
		//Iluminacion difusa
	
		vec3 lightDir = normalize( lightPosition[i] - Position );
		vec3 lightSpotDirection = normalize( lightSpotDirect[i] - lightPosition[i]);
		
		float intDifusa = dot(lightDir, Normal);
	
		//Si la cara esta del lado de la luz se aplica la iluminacion difusa y la especular
		if(intDifusa > 0.0) {
		
			//Si esta en el cono de la luz spot
			
			float angle = acos(dot(-lightDir, lightSpotDirection));
			float cutoff = radians( 90.0 );
			if( angle < cutoff ) {
				
				float spotFactor = pow(dot(-lightDir, lightSpotDirection),8);
				
				colorFinal += 0.5 * intDifusa * spotFactor * color;
				
				//Iluminacion especular
				
				//Vector de la posicion al ojo
				vec3 vista = normalize(vec3(-Position));
				
				vec3 h = normalize(vista + lightDir);
				
				colorFinal += vec3(0.5,0.5,0.5) * spotFactor * pow( max( dot(h,Normal), 0.0 ), 3.0);
					
			}
		}
	
	}
	
	FragColor = vec4( colorFinal, alpha);

	
}