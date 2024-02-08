#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform float color_r;

// texture sampler
uniform sampler2D texture1;


void main()
{
    // Use the texture1 sampler to sample the texture at TexCoord
    // Add rgb colors 
    // FragColor = texture(texture1, TexCoord);
    FragColor = vec4(color_r, 0.4824, 1.0, 0.8);
    FragColor += texture(texture1, TexCoord);
}
