#version 330 core

struct Material {
    sampler2D diffuse;
    vec3 cAmbient;
    vec3 cDiffuse;
    vec3 cSpecular;
    float shininess;
};

in vec3 fsPosition;
in vec3 fsNormal;
in vec2 fsTextureCoords;

uniform vec3 cameraPosition;
uniform Material material;

vec3 normal = normalize(fsNormal);
vec3 diffuseTexColor = vec3(texture(material.diffuse, fsTextureCoords));

vec3 ambientComponent(vec3 lightColor) {
    return lightColor * material.cAmbient * diffuseTexColor;
}

vec3 diffuseComponent(vec3 lightColor, vec3 lightDirection) {
    float diffuseCoeff = dot(normal, lightDirection);
    if (diffuseCoeff > 0.2) { diffuseCoeff = 1.0; }
    else if (diffuseCoeff > 0.0) { diffuseCoeff = 0.3; }
    else { diffuseCoeff = 0.0; }
    
    return lightColor * material.cDiffuse * diffuseCoeff * diffuseTexColor;
}

vec3 specularComponent(vec3 lightColor, vec3 lightDirection) {
    vec3 viewDirection = normalize(cameraPosition - fsPosition);
    vec3 reflectedDirection = reflect(-lightDirection, normal);
    
    float specularCoeff = pow(
        max(dot(viewDirection, reflectedDirection), 0.0),
        material.shininess
    );
    if (specularCoeff < 0.5) { specularCoeff = 0.0; }
    else { specularCoeff = 1.0; }
    
    return lightColor * material.cSpecular * specularCoeff;
}