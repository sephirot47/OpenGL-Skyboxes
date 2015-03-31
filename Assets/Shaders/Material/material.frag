#version 130	

struct Material
{
	sampler2D texture;
	vec3 diffuse, specular;
	float shininess, shineStrength;
};
uniform Material material;

in vec3 fpos;
in vec2 fuv;
in vec3 fnormal;

out vec4 outGColor;
out vec3 outGPosition;
out vec2 outGUv;
out vec3 outGNormal;

out vec4 outGMaterialTexture;
out vec3 outGMaterialDiffuse;
out vec3 outGMaterialSpecular;
out vec3 outGMaterialShininess;

void main()
{  
    outGColor = vec4(0, 0, 0, 1);
    outGPosition = fpos;
    outGUv = fuv;
    outGNormal = normalize(fnormal);

    outGMaterialTexture = vec4(texture(material.texture, vec2(fuv.x, 1.0 - fuv.y)).rgb, 1);
    outGMaterialDiffuse = material.diffuse;
    outGMaterialSpecular = material.specular;
    outGMaterialShininess = vec3(material.shininess);
}

