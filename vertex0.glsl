#version 330 core
layout (location =0) in vec3 aPos;
layout (location =1) in vec4 aColor;
layout (location =2) in vec2 aTextCoord;
layout (location =3) in vec3 aNormal;

out vec4 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int perspective;
uniform int wing;
uniform mat4 mod1;


void main()
{
    vec4 rotated;
    if (perspective ==1){
        if (wing == 1){
            rotated = mod1*vec4(aPos, 1.0);
            gl_Position = projection * view * model *rotated;

        } else {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }


    } else {
        gl_Position = vec4(aPos, 1.0);
    }
    ourColor = aColor;
    TexCoord = aTextCoord;
    Normal = aNormal;
    FragPos = vec3(gl_Position[0], gl_Position[1], gl_Position[2]);
}