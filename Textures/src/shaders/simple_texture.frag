#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main() {
	vec2 flippedTexCoord = vec2(1.0 - TexCoord.x, TexCoord.y);
	FragColor = mix(texture(texture1, TexCoord),
	                texture(texture2, flippedTexCoord), mixValue);	// 0.0 = 100% first texture, 1.0 = 100% second texture, .2 = 80% first texture
}