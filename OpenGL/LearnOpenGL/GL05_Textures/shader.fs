#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D containerTexture;

void main()
{
     FragColor = texture2D(containerTexture,TexCoord);
};