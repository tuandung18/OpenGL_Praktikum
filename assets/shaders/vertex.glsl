#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colorRGB;


out vec3 colorVS;

uniform mat4 mm;
uniform mat4 vm;
uniform mat4 pm;

void main(){
    colorVS = colorRGB;
    gl_Position = pm * vm * mm * vec4(pos, 1.0);

}
