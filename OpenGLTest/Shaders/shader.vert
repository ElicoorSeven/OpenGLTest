#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

out vec4 vertexColor;
out vec2 TexCoord;
out vec3 Normal;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1);
    vertexColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
    TexCoord = tex;
    Normal = mat3(transpose(inverse(model))) * normal;
}
