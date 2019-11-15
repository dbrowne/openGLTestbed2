#version 330 core
layout (location =0) in vec3 aPos;
layout (location =1) in vec4 aColor;
layout (location =2) in vec2 aTextCoord;

out vec4 ourColor;
out vec2 TexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int perspective;
void main()
{
    if (perspective ==1){
        gl_Position = projection * view * model * vec4(aPos, 1.0);
    } else {
        gl_Position = vec4(aPos, 1.0);
    }
    ourColor = aColor;
    TexCoord = aTextCoord;
}