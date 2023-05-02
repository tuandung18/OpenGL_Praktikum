#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 colorRGB;

out vec3 colorVS;

void main(){
    colorVS = colorRGB;
    gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);

}
