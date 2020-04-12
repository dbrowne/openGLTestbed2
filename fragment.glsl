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

uniform vec2 u_resolution;
uniform float u_time;
uniform int smokeFlag;
uniform int showSphere;
uniform int dotFlag;
uniform int headFlag;


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
uniform float bMult;

float random (in vec2 _st) {
    return fract(sin(dot(_st.xy,
    vec2(12.9898, 78.233)))*
    43758.5453123);
}

vec2 random2(vec2 p) {
    return fract(sin(vec2(dot(p, vec2(127.1, 311.7)), dot(p, vec2(269.5, 183.3))))*43758.5453);
}

vec2 random3(vec2 p) {
    return fract(sin(vec2(dot(p, vec2(227.1, 611.7)), dot(p, vec2(869.5, 183.3))))*93758.5453);
}


// from the book of shaders
vec3 voronoi(in vec2 x) {
    vec2 n = floor(x);
    vec2 f = fract(x);

    // first pass: regular voronoi
    vec2 mg, mr;
    float md = 8.0;
    for (int j= -1; j <= 1; j++) {
        for (int i= -1; i <= 1; i++) {
            vec2 g = vec2(float(i), float(j));
            vec2 o = random3(n + g);
            o = 0.5 + 0.5*sin(u_time + 6.2831*o);

            vec2 r = g + o - f;
            float d = dot(r, r);

            if (d<md) {
                md = d;
                mr = r;
                mg = g;
            }
        }
    }

    // second pass: distance to borders
    md = 8.0;
    for (int j= -2; j <= 2; j++) {
        for (int i= -2; i <= 2; i++) {
            vec2 g = mg + vec2(float(i), float(j));
            vec2 o = random3(n + g);
            o = 0.5 + 0.5*sin(u_time + 6.2831*o);

            vec2 r = g + o - f;

            if (dot(mr-r, mr-r)>0.00001) {
                md = min(md, dot(0.5*(mr+r), normalize(r-mr)));
            }
        }
    }
    return vec3(md, mr);
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

    #define NUM_OCTAVES 15

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


vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{

    if (smokeFlag ==1){
        vec2 st =FragPos.xy/u_resolution.xy*bMult;
        st += st * abs(sin(u_time*0.1)*3.0);
        vec3 color = vec3(0.0);
        vec2 q = vec2(0.);
        q.x = fbm(st + 0.00*u_time);
        q.y = fbm(st + vec2(1.0));

        vec2 r = vec2(0.);
        r.x = fbm(st + 1.0*q + vec2(1.7, 9.2)+ 0.15*u_time);
        r.y = fbm(st + 1.0*q + vec2(8.3, 2.8)+ 0.126*u_time);

        float f = fbm(st+r);

        color = mix(vec3(0.501961, 0.19608, 0.99),
        vec3(0.666667, 0.666667, 0.0498039),
        clamp((f*f)*4.0, 0.0, 1.0));

        color = mix(color,
        vec3(0, 0, 0.164706),
        clamp(length(q), 0.0, 1.0));

        color = mix(color,
        vec3(0.666667, 1, 1),
        clamp(length(r.x), 0.0, 1.0));

        if (showSphere ==1){

            vec3 viewDir = normalize(viewPos - FragPos);

            // ambient
            float ambientStrength = 0.01;
            vec3 ambient = ambientStrength * lightColor;

            // diffuse
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(lightPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diff * lightColor;
            //            vec3  result = (ambient + diffuse)*vec3(ourColor[0], ourColor[1], ourColor[2]);
            vec3 result = ambient+diffuse;


            FragColor = vec4((f*f*f+.6*f*f+.5*f)*color*result, 1.);
        } else {
            FragColor = vec4((f*f*f+.6*f*f+.5*f)*color, 1.);
        }

    } else if (dotFlag ==1){
        // Cellular noise
        vec2 st = FragPos.xy/u_resolution.xy*800.;
        st.x *= u_resolution.x/u_resolution.y;
        vec3 color = vec3(.3, .8, .3);

        // Scale
        st *= 3.;

        // Tile the space
        vec2 i_st = floor(st);
        vec2 f_st = fract(st);

        float m_dist = 1.;// minimun distance

        for (int y= -1; y <= 1; y++) {
            for (int x= -1; x <= 1; x++) {
                // Neighbor place in the grid
                vec2 neighbor = vec2(float(x), float(y));

                // Random position from current + neighbor place in the grid
                vec2 point = random2(i_st + neighbor);

                // Animate the point
                point = 0.5 + 0.5*sin(u_time + 6.2831*point);

                // Vector between the pixel and the point
                vec2 diff = neighbor + point - f_st;

                // Distance to the point
                float dist = length(diff);

                // Keep the closer distance
                m_dist = min(m_dist, dist);
            }
        }

        // Draw the min distance (distance field)
        color += .6*m_dist;

        // Draw cell center
        color += .03-step(.02, m_dist);

        // Show isolines
        color -= step(.7, abs(sin(27.0*m_dist)))*.5;

        // ambient
        float ambientStrength = 0.01;
        vec3 ambient = ambientStrength * lightColor;

        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        vec3  result = (ambient + diffuse)*vec3(color[0], color[1], color[2]);



        FragColor = vec4(result.rgb, 1.0);
    } else if (headFlag ==1){
        vec2 st = FragPos.xy/u_resolution.xy*160.;
        st.x *= u_resolution.x/u_resolution.y;
        vec3 color = vec3(.5, 1.0, .8);

        // Scale
        st *= 3.;
        vec3 c = voronoi(st);

        // isolines
        color = c.x*(0.5 + 0.5*sin(64.0*c.x))*vec3(1.0);
        // borders
        color = mix(vec3(1.0), color, smoothstep(0.01, 0.02, c.x));
        // feature points
        float dd = length(c.yz);
        color += vec3(1.)*(1.0-smoothstep(0.0, 0.04, dd));

        float ambientStrength = 0.01;
        vec3 ambient = ambientStrength * lightColor;

        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        vec3  result = (ambient + diffuse)*vec3(color[0]*ourColor[0], color[1]*ourColor[1], color[2]*ourColor[2]);




        FragColor = vec4(result, 1.0);
    }

    else {


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
}

