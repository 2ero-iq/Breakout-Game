#version 410 core

layout(location = 0) in vec2 aPos;

uniform mat4 Projection = mat4(1);
uniform mat4 Model = mat4(1);
uniform mat4 View = mat4(1);

void main()
{
    gl_Position = Projection * View * Model * vec4(aPos, 0.0f, 1.0f);
}
