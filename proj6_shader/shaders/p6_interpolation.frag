#version 330 core

out vec4 outClr;
in vec3 ourColor;
in vec3 ourPos;
void main(){
    // outClr = vec4(ourColor, 1);
    outClr = vec4(ourPos.x, ourPos.y, ourPos.z, 1);
}