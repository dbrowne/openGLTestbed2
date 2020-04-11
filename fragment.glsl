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
uniform int useTex;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;
uniform Light light;


float random (in vec2 _st) {
    return fract(sin(dot(_st.xy,
    vec2(12.9898, 78.233)))*
    43758.5453123);
}

// Based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 _st) {
    vec2 i = floor(_st);
    vec2 f = fract(_st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
    (c - a)* u.y * (1.0 - u.x) +
    (d - b) * u.x * u.y;
}

    #define NUM_OCTAVES 5

float fbm (in vec2 _st) {
    float v = 0.0;
    float a = 0.5;
    vec2 shift = vec2(100.0);
    // Rotate to reduce axial bias
    mat2 rot = mat2(cos(0.5), sin(0.5),
    -sin(0.5), cos(0.50));
    for (int i = 0; i < NUM_OCTAVES; ++i) {
        v += a * noise(_st);
        _st = rot * _st * 2.0 + shift;
        a *= 0.5;
    }
    return v;
}




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
            if (useTex == 1){
                FragColor = texture(texture2, TexCoord) * vec4(result, 1.0);
            } else {
                FragColor = texture(texture1, TexCoord) * vec4(result, 1.0);
            }
        }
        if (texflag == 1){
            FragColor = vec4(result, 1.0);;
        }
        if (texflag == 2){
            if (useTex ==1){
                FragColor = texture(texture2, TexCoord);
            } else {
                FragColor = texture(texture1, TexCoord);
            }

        }


    } else if (lightFlag ==1){

        if (texflag == 0){
            if (useTex ==1){
                FragColor = texture(texture2, TexCoord) * vec4(ourColor);
            } else {
                FragColor = texture(texture1, TexCoord) * vec4(ourColor);
            }
        }
        if (texflag == 1){
            FragColor = vec4(ourColor);
        }
        if (texflag == 2){
            if (useTex ==1){
                FragColor = texture(texture2, TexCoord);
            } else {
                FragColor = texture(texture1, TexCoord);
            }
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