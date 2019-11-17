#version 330 core
out vec4 FragColor;
in vec4 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
uniform sampler2D texture1;
uniform int texflag;
uniform int lightFlag;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{

    if (lightFlag == -1){

        if (texflag == 0){
            FragColor = texture(texture1, TexCoord) * vec4(ourColor);
        }
        if (texflag == 1){
            FragColor = vec4(ourColor);
        }
        if (texflag == 2){
            FragColor = texture(texture1, TexCoord);
        }
    } else {
        // ambient
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;

        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        vec3 result = (ambient + diffuse) * objectColor;
        FragColor = vec4(result, 1.0);

        if (texflag == 0){
            FragColor = texture(texture1, TexCoord) * vec4(result, 1.0);;
        }
        if (texflag == 1){
            FragColor = vec4(result, 1.0);;
        }
        if (texflag == 2){
            FragColor = texture(texture1, TexCoord);
        }

    }
}