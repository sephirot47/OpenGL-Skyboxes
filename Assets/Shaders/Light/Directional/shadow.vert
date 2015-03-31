#version 130

uniform mat4 PVM;

in vec3 pos;

void main()
{  
    gl_Position = PVM * vec4(pos, 1.0);
}

