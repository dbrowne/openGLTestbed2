#version 330 core
out vec4 FragColor;
in vec4 ourColor;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform int texflag;
void main()
{
    if (texflag == 0){
        FragColor = texture(texture1, TexCoord) * vec4(ourColor);
    }
    if (texflag == 1){
        FragColor = vec4(ourColor);
    }
    if (texflag == 2){
        FragColor = texture(texture1, TexCoord);
    }

}