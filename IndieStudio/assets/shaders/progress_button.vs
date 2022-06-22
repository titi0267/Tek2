#version 330

// Input vertex attributes
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;

// Input uniform values
uniform mat4 mvp;

// Output vertex attributes (to fragment shader)
out vec2 fragTexCoord;
out vec4 fragColor;
out float fragPercent;

const float BUTTON_SIZE = 3;

void main()
{
    // Send vertex attributes to fragment shader
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;
    fragPercent = (vertexPosition.x + BUTTON_SIZE / 2.0) / BUTTON_SIZE;

    // Calculate final vertex position
    gl_Position = mvp*vec4(vertexPosition, 1.0);
}
