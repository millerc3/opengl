#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 VertexColor;

uniform bool hasTexture;
uniform sampler2D _texture;

void main() {
	if (hasTexture) {
		FragColor = texture(_texture, TexCoord);
	}
	else {
		FragColor = vec4(VertexColor, 1.0f);
	}
}