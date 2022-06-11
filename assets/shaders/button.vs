#version 330

// Input vertex attributes
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;

// Input uniform
uniform mat4 mvp;
uniform mat4 matModel;

// Output vertex attributes (-> fragment shader)
out vec3 fragPosition;
out vec2 fragTexCoord;
out vec4 fragColor;

void main()
{
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;
    fragPosition = vec3(matModel * vec4(vertexPosition, 1.0));

    gl_Position = mvp * vec4(vertexPosition, 1.0);;
}
