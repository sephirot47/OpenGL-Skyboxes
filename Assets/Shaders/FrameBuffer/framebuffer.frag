#version 130	

uniform sampler2D GColor;
in vec2 screenuv;

void main()
{ 
    gl_FragColor = vec4(texture(GColor, screenuv).rgb, 1);
}

