#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D textureWall;
uniform sampler2D textureFace;

void main()
{
//    gl_FragColor =mix( texture2D(textureWall,TexCoord),texture2D(textureFace,vec2(1.0-TexCoord.x,1.0-TexCoord.y)),0.2);
    gl_FragColor = texture2D(textureWall,TexCoord);
}
