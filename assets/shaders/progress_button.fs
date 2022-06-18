#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;
in float fragPercent;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

uniform float progress;
uniform vec4 progressColor;

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord);

    // NOTE: Implement here your fragment shader code

    if (fragPercent <= progress)
    {
        finalColor = texelColor * progressColor;
    }
    else
    {
        finalColor = texelColor * colDiffuse;
    }
}
