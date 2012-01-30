#version 400

in vec3 VertexPosition;
in vec3 VertexColor;
in vec3 VertexNormal;
in vec2 TextureCoord;

out vec3 Normal;
out vec3 Position;
out vec2 TexCoord;
out vec3 ReflectDir;

uniform mat4 inverseMatrix;
uniform vec3 camPos;

void main()
{
	TexCoord = TextureCoord;
	Normal = normalize( gl_NormalMatrix * VertexNormal );
	Position = vec3(gl_ModelViewMatrix * vec4( VertexPosition, 1.0));
	
	vec3 worldPos = vec3( inverseMatrix * gl_ModelViewMatrix *vec4(VertexPosition,1.0) );
	
	vec3 worldNorm = vec3( inverseMatrix * gl_ModelViewMatrix *vec4(VertexNormal,0.0) );
	
	vec3 worldView = normalize( camPos - worldPos );
	
	ReflectDir = reflect(-worldView, worldNorm );
	
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4( VertexPosition, 1.0);
}