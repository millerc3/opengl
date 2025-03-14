#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;	// output a color to the fragment shader

uniform vec3 offset;  // ex2: add an offset uniform

void main()
{
	gl_Position = vec4(-aPos + offset, 1.0);		//ex1: just make this negative
	ourColor = aColor;
}