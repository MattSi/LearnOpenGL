#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

vec3 inverseClr(){
    return vec3(1.0 - texture(screenTexture, TexCoords));
} 

vec3 grayscale(){
    vec3 outColor = texture(screenTexture, TexCoords).rgb;
    float avg = (outColor.r + outColor.g + outColor.b)/3.0;
    return vec3(avg, avg, avg);
}


void main()
{    
    FragColor = texture(screenTexture, TexCoords);
} 