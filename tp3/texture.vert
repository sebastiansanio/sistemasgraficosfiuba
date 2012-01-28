#version 130

in vec3 VertexPosition;
in vec3 VertexColor;
in vec3 VertexNormal;
in vec2 TextureCoord;

out vec3 Normal;
out vec3 Position;
out vec2 TexCoord;

void main()
{
	TexCoord = TextureCoord;
	Normal = normalize( gl_NormalMatrix * VertexNormal );
	Position = vec3(gl_ModelViewMatrix * vec4( VertexPosition, 1.0));
	
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4( VertexPosition, 1.0);
}