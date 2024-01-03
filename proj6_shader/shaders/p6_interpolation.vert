#version 330 core

layout (location=0) in vec3 pos;
layout (location=1) in vec3 clr;

out vec3 ourColor;
out vec3 ourPos;
uniform float offset;
void main(){
    ourColor = clr;
    ourPos = pos;
    gl_Position=vec4(pos.x+offset,pos.y,pos.z,1.0);
}