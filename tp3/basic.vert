#version 400

in vec3 VertexPosition;
in vec3 VertexColor;
in vec3 VertexNormal;

out vec3 Color;
out vec3 Normal;
out vec3 Position;

void main()
{
	Color = VertexColor;
	Normal = normalize( gl_NormalMatrix * VertexNormal );
	Position = vec3(gl_ModelViewMatrix * vec4( VertexPosition, 1.0));
	
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4( VertexPosition, 1.0);
}