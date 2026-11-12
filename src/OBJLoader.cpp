#include "OBJLoader.h"

#include <array>
#include <algorithm>
#include <fstream>
#include <sstream>

OBJLoader::MeshInfo OBJLoader::getMeshInfo(const std::string& filepath){
    std::ifstream file(filepath);
    std::string line;

    if (!file.is_open()) {
        return {};
    }

    std::vector<std::array<float, 3>> vertexPos;
    std::vector<std::array<float, 3>> vertexNormal;
    std::vector<std::array<float, 2>> textureCoords;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    unsigned int index = 0; // we need a counter for index of every set of 8 vertices to add


    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string prefix;
        stream >> prefix;

        if (prefix == "v"){
            float x, y, z;
            stream >> x >> y >> z;
            vertexPos.push_back({x, y, z});
        }
        else if (prefix == "vt"){
            float u, v;
            stream >> u >> v;
            textureCoords.push_back({u, v});
        }
        else if(prefix == "vn") {
            float x, y, z;
            stream >> x >> y >> z;
            vertexNormal.push_back({x, y, z});
        }
        else if(prefix == "f"){
            std::string chunk;
            while (stream >> chunk) {
                std::replace(chunk.begin(), chunk.end(), '/', ' ');
                std::istringstream parser(chunk);

                int vIndex, tIndex, nIndex;
                parser >> vIndex >> tIndex >> nIndex;

                const std::array<float, 3>& pos = vertexPos.at(vIndex - 1); 
                const std::array<float, 3>& norm = vertexNormal.at(nIndex - 1);
                const std::array<float, 2>& tex = textureCoords.at(tIndex - 1);

                vertices.insert(vertices.end(), {
                    pos[0], pos[1], pos[2],
                    norm[0], norm[1], norm[2],
                    tex[0], tex[1]
                });
                indices.push_back(index++);
            }   
        }
    }
    file.close();

    MeshInfo mesh;
    mesh.vertices = vertices;
    mesh.indices = indices;

    return mesh;
}



/*



# Example: square.obj
# Comments begin with #

# Material library
mtllib square.mtl

# Object name
o Square

# Vertex positions (x y z)
v -1.0 -1.0 0.0
v  1.0 -1.0 0.0
v  1.0  1.0 0.0
v -1.0  1.0 0.0

# Texture coordinates (u v)
vt 0.0 0.0
vt 1.0 0.0
vt 1.0 1.0
vt 0.0 1.0

# Vertex normals (nx ny nz)
vn 0.0 0.0 1.0

# Group name
g FrontFace

# Material assignment
usemtl DefaultMaterial

# Smoothing disabled
s off

# Triangle faces
f 1/1/1 2/2/1 3/3/1
f 1/1/1 3/3/1 4/4/1




*/