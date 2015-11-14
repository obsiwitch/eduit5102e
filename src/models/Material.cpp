#include "models/Material.hpp"

Material::Material(const aiMaterial& material, std::string directory) {
    loadTexture(material, directory, aiTextureType_DIFFUSE);
    
    aiColor3D color;
    
    material.Get(AI_MATKEY_COLOR_AMBIENT, color);
    cAmbient = glm::vec4(color.r, color.g, color.b, 1.0f);
    
    material.Get(AI_MATKEY_COLOR_DIFFUSE, color);
    cDiffuse = glm::vec4(color.r, color.g, color.b, 1.0f);
    
    material.Get(AI_MATKEY_COLOR_SPECULAR, color);
    cSpecular = glm::vec4(color.r, color.g, color.b, 1.0f);
    
    material.Get(AI_MATKEY_SHININESS, shininess);
}

void Material::loadTexture(
    const aiMaterial& material, std::string directory, aiTextureType type
) {
    if (material.GetTextureCount(type) > 0) {
        aiString textureFile;
        material.GetTexture(type, 0, &textureFile);
        
        int opacity;
        material.Get(AI_MATKEY_OPACITY, opacity);
        
        std::string texturePath = directory + '/' + std::string(textureFile.C_Str());
        textures.push_back(Texture2D(
            texturePath, GL_TEXTURE0, !opacity
        ));
    }
}

void Material::update(Shader& shader) {
    shader.setUniform("material.diffuse", (GLuint) 0);
    shader.setUniform("material.cAmbient", cAmbient);
    shader.setUniform("material.cDiffuse", cDiffuse);
    shader.setUniform("material.cSpecular", cSpecular);
    shader.setUniform("material.shininess", shininess);
}

void Material::bindTextures() {
    for (Texture2D& texture : textures) {
        texture.bind();
    }
}

void Material::unbindTextures() {
    for (Texture2D& texture : textures) {
        texture.unbind();
    }
}
