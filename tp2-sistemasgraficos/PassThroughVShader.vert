#version 400

in vec3 VertexPosition;
in vec3 VertexColor;

out vec3 Color;

uniform mat4 RotationMatrixy;
uniform mat4 RotationMatrixx;

void main()
{
	Color = VertexColor;
	gl_Position = RotationMatrixx * RotationMatrixy * vec4( VertexPosition, 1.0);
}