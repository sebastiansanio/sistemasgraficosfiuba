#version 400

in vec3 VertexPosition;
in vec3 VertexColor;

out vec3 Color;

void main()
{
	Color = VertexColor;
	
	gl_Position = vec4( VertexPosition + vec3(0.5,0.5,0.0) , 1.0);
}