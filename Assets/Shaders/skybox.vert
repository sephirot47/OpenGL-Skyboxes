#version 130	

uniform samplerCube skybox;
in vec2 screenuv;

void main()
{
    gl_FragColor = vec4(texture(GColor, screenuv).rgb, 1);
}
