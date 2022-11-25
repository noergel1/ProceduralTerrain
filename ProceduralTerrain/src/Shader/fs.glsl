#version 460 core

in VS_OUT {

    vec3 FragPos;
	vec2 TexCoord;

} fs_in;

layout(location = 0) out vec4 Output;

uniform sampler2D diffuse;

void main()
{
	Output = vec4(vec3(texture(diffuse, fs_in.TexCoord)),1.0f);
}