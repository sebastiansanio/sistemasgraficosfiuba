#version 400

in vec3 Color;
in vec3 Light;
in vec3 Normal;
in vec3 Position;

out vec4 FragColor;

void main()
{
	float intAmbiente = 0.2;
	
	vec3 s1 = normalize( Light - Position );
	
	float intDifusa = max( dot(s1, Normal), 0.0 );
	
	vec3 colorFinal = ( intAmbiente + intDifusa ) * Color;
	
	FragColor = vec4( colorFinal, 1.0) ;
}