#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out VS_OUT {

    vec3 FragPos;
	vec2 TexCoord;

} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vs_out.FragPos = vec3(model * vec4(aPos, 1.0f));
	vs_out.TexCoord = aTexCoord;
	gl_Position = projection * view * vec4(vs_out.FragPos, 1.0f);
}