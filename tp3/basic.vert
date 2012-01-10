#version 400

in vec3 VertexPosition;
in vec3 VertexColor;
in vec3 VertexNormal;

out vec3 Color;

uniform mat4 ModelViewMatrix;

uniform mat4 ProjectionMatrix;

void main()
{
	Color = VertexColor;
	
	gl_Position = ProjectionMatrix * ModelViewMatrix * vec4( VertexPosition, 1.0);
}