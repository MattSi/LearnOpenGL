#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;
out mat4 FragView;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 inv_view_model;

void main(){
    FragPos = vec3(view * model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inv_view_model)) * aNormal;
    FragView = view;
    gl_Position = projection * vec4(FragPos, 1.0);
}