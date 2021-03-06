#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/mesh.h>

#include "shaders/Shader.hpp"
#include "models/Vertex.hpp"
#include "models/Material.hpp"

class Mesh {
public:
    Mesh(const aiMesh& mesh, const aiMaterial& material, std::string directory);
    
    void draw(Shader& shader);
    
private:
    GLuint vertexArray;
        
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    Material material;
    
    void createBuffers();
};


#endif // MESH_HPP
