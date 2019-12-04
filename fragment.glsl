#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform int texflag;
uniform int lightFlag;
uniform vec3 lightPos;
uniform vec3 lightPos2;
uniform vec3 lightColor2;
uniform SpotLight spotLight;
uniform Material material;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;
uniform Light light;


vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{

    if (lightFlag == 0){
        vec3 viewDir = normalize(viewPos - FragPos);

        // ambient
        float ambientStrength = 0.01;
        vec3 ambient = ambientStrength * lightColor;

        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        vec3  result = (ambient + diffuse)*vec3(ourColor[0], ourColor[1], ourColor[2]);
        //        vec3 result = (ambient + diffuse) * objectColor;


        //        FragColor = vec4(result, 1.0);

        if (texflag == 0){
            FragColor = texture(texture1, TexCoord) * vec4(result, 1.0);;
        }
        if (texflag == 1){
            FragColor = vec4(result, 1.0);;
        }
        if (texflag == 2){
            FragColor = texture(texture1, TexCoord);
        }


    } else if (lightFlag ==1){

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
    else
    {
        vec3 viewDir = normalize(viewPos - FragPos);

        vec3 norm = normalize(Normal);

        vec3 result =CalcSpotLight(spotLight, norm, FragPos, viewDir);

        FragColor = vec4(result, 1.0);

    }
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    //    return (ambient + diffuse + specular);
    return lightDir;
}