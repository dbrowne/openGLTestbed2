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
uniform int tailFlag;
uniform float tailMult;

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

// Cellular noise ("Worley noise") in 3D in GLSL.
// Copyright (c) Stefan Gustavson 2011-04-19. All rights reserved.
// This code is released under the conditions of the MIT license.
// See LICENSE file for details.

// Permutation polynomial: (34x^2 + x) mod 289
vec3 permute(vec3 x) {
    return mod((34.0 * x + 1.0) * x, 289.0);
}

// Cellular noise, returning F1 and F2 in a vec2.
// 3x3x3 search region for good F2 everywhere, but a lot
// slower than the 2x2x2 version.
// The code below is a bit scary even to its author,
// but it has at least half decent performance on a
// modern GPU. In any case, it beats any software
// implementation of Worley noise hands down.

vec2 cellular(vec3 P) {
    #define K 0.142857142857// 1/7
    #define Ko 0.428571428571// 1/2-K/2
    #define K2 0.020408163265306// 1/(7*7)
    #define Kz 0.166666666667// 1/6
    #define Kzo 0.416666666667// 1/2-1/6*2
    #define jitter 1.0// smaller jitter gives more regular pattern

    vec3 Pi = mod(floor(P), 289.0);
    vec3 Pf = fract(P) - 0.5;

    vec3 Pfx = Pf.x + vec3(1.0, 0.0, -1.0);
    vec3 Pfy = Pf.y + vec3(1.0, 0.0, -1.0);
    vec3 Pfz = Pf.z + vec3(1.0, 0.0, -1.0);

    vec3 p = permute(Pi.x + vec3(-1.0, 0.0, 1.0));
    vec3 p1 = permute(p + Pi.y - 1.0);
    vec3 p2 = permute(p + Pi.y);
    vec3 p3 = permute(p + Pi.y + 1.0);

    vec3 p11 = permute(p1 + Pi.z - 1.0);
    vec3 p12 = permute(p1 + Pi.z);
    vec3 p13 = permute(p1 + Pi.z + 1.0);

    vec3 p21 = permute(p2 + Pi.z - 1.0);
    vec3 p22 = permute(p2 + Pi.z);
    vec3 p23 = permute(p2 + Pi.z + 1.0);

    vec3 p31 = permute(p3 + Pi.z - 1.0);
    vec3 p32 = permute(p3 + Pi.z);
    vec3 p33 = permute(p3 + Pi.z + 1.0);

    vec3 ox11 = fract(p11*K) - Ko;
    vec3 oy11 = mod(floor(p11*K), 7.0)*K - Ko;
    vec3 oz11 = floor(p11*K2)*Kz - Kzo;// p11 < 289 guaranteed

    vec3 ox12 = fract(p12*K) - Ko;
    vec3 oy12 = mod(floor(p12*K), 7.0)*K - Ko;
    vec3 oz12 = floor(p12*K2)*Kz - Kzo;

    vec3 ox13 = fract(p13*K) - Ko;
    vec3 oy13 = mod(floor(p13*K), 7.0)*K - Ko;
    vec3 oz13 = floor(p13*K2)*Kz - Kzo;

    vec3 ox21 = fract(p21*K) - Ko;
    vec3 oy21 = mod(floor(p21*K), 7.0)*K - Ko;
    vec3 oz21 = floor(p21*K2)*Kz - Kzo;

    vec3 ox22 = fract(p22*K) - Ko;
    vec3 oy22 = mod(floor(p22*K), 7.0)*K - Ko;
    vec3 oz22 = floor(p22*K2)*Kz - Kzo;

    vec3 ox23 = fract(p23*K) - Ko;
    vec3 oy23 = mod(floor(p23*K), 7.0)*K - Ko;
    vec3 oz23 = floor(p23*K2)*Kz - Kzo;

    vec3 ox31 = fract(p31*K) - Ko;
    vec3 oy31 = mod(floor(p31*K), 7.0)*K - Ko;
    vec3 oz31 = floor(p31*K2)*Kz - Kzo;

    vec3 ox32 = fract(p32*K) - Ko;
    vec3 oy32 = mod(floor(p32*K), 7.0)*K - Ko;
    vec3 oz32 = floor(p32*K2)*Kz - Kzo;

    vec3 ox33 = fract(p33*K) - Ko;
    vec3 oy33 = mod(floor(p33*K), 7.0)*K - Ko;
    vec3 oz33 = floor(p33*K2)*Kz - Kzo;

    vec3 dx11 = Pfx + jitter*ox11;
    vec3 dy11 = Pfy.x + jitter*oy11;
    vec3 dz11 = Pfz.x + jitter*oz11;

    vec3 dx12 = Pfx + jitter*ox12;
    vec3 dy12 = Pfy.x + jitter*oy12;
    vec3 dz12 = Pfz.y + jitter*oz12;

    vec3 dx13 = Pfx + jitter*ox13;
    vec3 dy13 = Pfy.x + jitter*oy13;
    vec3 dz13 = Pfz.z + jitter*oz13;

    vec3 dx21 = Pfx + jitter*ox21;
    vec3 dy21 = Pfy.y + jitter*oy21;
    vec3 dz21 = Pfz.x + jitter*oz21;

    vec3 dx22 = Pfx + jitter*ox22;
    vec3 dy22 = Pfy.y + jitter*oy22;
    vec3 dz22 = Pfz.y + jitter*oz22;

    vec3 dx23 = Pfx + jitter*ox23;
    vec3 dy23 = Pfy.y + jitter*oy23;
    vec3 dz23 = Pfz.z + jitter*oz23;

    vec3 dx31 = Pfx + jitter*ox31;
    vec3 dy31 = Pfy.z + jitter*oy31;
    vec3 dz31 = Pfz.x + jitter*oz31;

    vec3 dx32 = Pfx + jitter*ox32;
    vec3 dy32 = Pfy.z + jitter*oy32;
    vec3 dz32 = Pfz.y + jitter*oz32;

    vec3 dx33 = Pfx + jitter*ox33;
    vec3 dy33 = Pfy.z + jitter*oy33;
    vec3 dz33 = Pfz.z + jitter*oz33;

    vec3 d11 = dx11 * dx11 + dy11 * dy11 + dz11 * dz11;
    vec3 d12 = dx12 * dx12 + dy12 * dy12 + dz12 * dz12;
    vec3 d13 = dx13 * dx13 + dy13 * dy13 + dz13 * dz13;
    vec3 d21 = dx21 * dx21 + dy21 * dy21 + dz21 * dz21;
    vec3 d22 = dx22 * dx22 + dy22 * dy22 + dz22 * dz22;
    vec3 d23 = dx23 * dx23 + dy23 * dy23 + dz23 * dz23;
    vec3 d31 = dx31 * dx31 + dy31 * dy31 + dz31 * dz31;
    vec3 d32 = dx32 * dx32 + dy32 * dy32 + dz32 * dz32;
    vec3 d33 = dx33 * dx33 + dy33 * dy33 + dz33 * dz33;

    // Sort out the two smallest distances (F1, F2)

    // Do it right and sort out both F1 and F2
    vec3 d1a = min(d11, d12);
    d12 = max(d11, d12);
    d11 = min(d1a, d13);// Smallest now not in d12 or d13
    d13 = max(d1a, d13);
    d12 = min(d12, d13);// 2nd smallest now not in d13
    vec3 d2a = min(d21, d22);
    d22 = max(d21, d22);
    d21 = min(d2a, d23);// Smallest now not in d22 or d23
    d23 = max(d2a, d23);
    d22 = min(d22, d23);// 2nd smallest now not in d23
    vec3 d3a = min(d31, d32);
    d32 = max(d31, d32);
    d31 = min(d3a, d33);// Smallest now not in d32 or d33
    d33 = max(d3a, d33);
    d32 = min(d32, d33);// 2nd smallest now not in d33
    vec3 da = min(d11, d21);
    d21 = max(d11, d21);
    d11 = min(da, d31);// Smallest now in d11
    d31 = max(da, d31);// 2nd smallest now not in d31
    d11.xy = (d11.x < d11.y) ? d11.xy : d11.yx;
    d11.xz = (d11.x < d11.z) ? d11.xz : d11.zx;// d11.x now smallest
    d12 = min(d12, d21);// 2nd smallest now not in d21
    d12 = min(d12, d22);// nor in d22
    d12 = min(d12, d31);// nor in d31
    d12 = min(d12, d32);// nor in d32
    d11.yz = min(d11.yz, d12.xy);// nor in d12.yz
    d11.y = min(d11.y, d12.z);// Only two more to go
    d11.y = min(d11.y, d11.z);// Done! (Phew!)
    return sqrt(d11.xy);// F1, F2
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

    } else if (tailFlag ==1){
        vec2 st = FragPos.xy/u_resolution.xy*tailMult*6.0;
        st *= 10.;

        vec2 F = cellular(vec3(st, u_time));
        float dots = smoothstep(0.005, 0.01, F.x);
        float n = F.y-F.x;

        n *= dots;

        float ambientStrength = 0.01;
        vec3 ambient = ambientStrength * lightColor;
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        vec3  result = (ambient + diffuse)*vec3(n*ourColor[0], n*ourColor[1], n*ourColor[2]);
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

