#version 130

uniform mat4 PVM, projection, view, model;
 
in vec3 inpos;

out vec3 fpos;

void main()
{    
    fpos = (vec4(inpos,1)).xyz;
    gl_Position = PVM * vec4(inpos, 1);
}

