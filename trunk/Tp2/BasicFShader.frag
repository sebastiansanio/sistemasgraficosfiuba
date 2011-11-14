#version 400

in vec3 Color;
in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D Tex1;

uniform vec3 FuenteLuz1;

uniform vec3 FuenteLuz2;

uniform int EncFuente1;

uniform int EncFuente2;

void main()
{
	
	vec3 colormaterial = Color;
	colormaterial = vec3(texture( Tex1, TexCoord ));

	vec3 colorfinal;

	//Modelo de Phong
	vec3 vista = vec3(-Position);
	vec3 brilloespecular = vec3(0.8,0.8,0.8);
	float brillodifusa = 0.5;
	float luzambiente = 0.2;
	float foco = 4.0;

	//Luz ambiente

	vec3 colorambiente = colormaterial * luzambiente;

	colorfinal = colorambiente;

	vec3 n = normalize(Normal);

	//Primera fuente de luz

	if(EncFuente1 != 0){

		vec3 s1 = normalize( FuenteLuz1 - Position );
	
		vec3 colordifusa1 = brillodifusa * colormaterial * max( dot(s1, n), 0.0 );

		vec3 h1 = normalize(s1 + vista);

		vec3 colorespecular1 = brilloespecular * pow( max( dot(h1,n), 0.0 ), foco);

		colorfinal = colorfinal + colordifusa1 + colorespecular1;

	}

	//Segunda fuente de luz

	if(EncFuente2 != 0){

	vec3 s2 = normalize( FuenteLuz2 - Position );
	
	vec3 colordifusa2 = brillodifusa * colormaterial * max( dot(s2, n), 0.0 );

	vec3 h2 = normalize(s2 + vista);

	vec3 colorespecular2 = brilloespecular * pow( max( dot(h2,n), 0.0 ), foco);

	colorfinal = colorfinal + colordifusa2 + colorespecular2;

	}

	FragColor = vec4(colorfinal, 1.0);
}