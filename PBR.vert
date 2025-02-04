#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;


uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
out vec3 WorldPos;  
out vec3 Normal;
out vec2 TexCoords;
void main()
{
	gl_Position =projMat*viewMat*modelMat* vec4(aPos.x, aPos.y, aPos.z, 1.0);
	WorldPos= vec3(modelMat * vec4(aPos, 1.0));
	Normal = aNormal;
	TexCoords = aTexCoords;
};