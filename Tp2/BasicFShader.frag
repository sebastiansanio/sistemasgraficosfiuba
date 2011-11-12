#version 400

in vec3 Color;
in vec3 Position;
in vec3 Normal;

out vec4 FragColor;

void main()
{
	vec3 fuenteluz = vec3(0.0,0.0,-1.0);
	//Ver
	vec3 vista = vec3(-Position);
	vec3 ks = vec3(1.0,1.0,1.0);
	float brillodifusa = 0.5;
	float luzambiente = 0.3;
	float brillo = 4.0;

	vec3 s = normalize( fuenteluz - Position );
	vec3 n = normalize(Normal);

	vec3 colorambiente = Color * luzambiente;

	vec3 colordifusa = brillodifusa * Color * max( dot(s, n), 0.0 );

	vec3 h = normalize(s + vista);

	vec3 colorespecular = ks * pow( max( dot(h,n), 0.0 ), brillo);

	FragColor = vec4( colorambiente + colordifusa + colorespecular, 1.0);
}