#version 330

#define MAX_LIGHTS 32
#define LIGHT_POINT 0
#define LIGHT_DIRECTIONAL 1

struct Light
{
    int enabled;
    int type;
    vec3 pos;
    vec3 dir;
    vec4 color;
};

// Input vertex attributes
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec3 fragNormal;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform Light lights[MAX_LIGHTS];
uniform vec4 ambient;
uniform vec3 viewPos;

// Output vertex attributes (to fragment shader)
out vec4 finalColor;

const float LIGHT_ATTENUATION = 0.2;

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord);
    vec3 normal = normalize(fragNormal);
    vec3 viewVec = normalize(viewPos - fragPosition);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    for (int i = 0; i < MAX_LIGHTS; i++) {
        if (lights[i].enabled == 1) {
            vec3 light = vec3(0.0);
            float attenuation = 1.0;

            if (lights[i].type == LIGHT_DIRECTIONAL)
            {
                light = -normalize(lights[i].dir);
            }

            if (lights[i].type == LIGHT_POINT)
            {
                light = normalize(lights[i].pos - fragPosition);
                attenuation = 1.0 / (1.0 + LIGHT_ATTENUATION * pow(distance(lights[i].pos, fragPosition), 2));
            }

            float normalDotLight = max(dot(normal, light), 0.0);
            diffuse += lights[i].color.rgb * normalDotLight * attenuation;

            vec3 reflectDir = reflect(-light, normal);
            float viewDotReflect = max(dot(viewVec, reflectDir), 0.0);
            float spec = pow(viewDotReflect, 16.0);
            specular += 0.5 * lights[i].color.rgb * spec * attenuation;
        }
    }

    finalColor = (ambient + vec4(diffuse, 1.0) + vec4(specular, 1.0)) * texelColor * colDiffuse;
}
