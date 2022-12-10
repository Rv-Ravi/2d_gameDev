!#!shader vertex
#version 450 core
layout(location = 0) in vec3 vertexPts;
layout(location = 1) in vec3 vertexCol;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 vertexNorm;


uniform mat4 transMat;
uniform mat4 viewProj;

void main()
{
	gl_Position = viewProj * transMat * vec4(vertexPts, 1.f);

}

!#!shader fragment
#version 450 core

out vec4 frgCol;

uniform vec3 uColor;

void main()
{
	frgCol = vec4(uColor,1.f);
}
