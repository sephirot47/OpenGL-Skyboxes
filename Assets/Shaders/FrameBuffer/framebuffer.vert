#version 130

in vec3 pos;
out vec2 screenuv; 

void main()
{  
    gl_Position = vec4(pos, 1.0);
    screenuv = pos.xy*0.5 + vec2(0.5);
}

