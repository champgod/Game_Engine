#include "OBJLOADER.h"

#include <array>
#include <vector>

MeshInfo OBJLoader::getMeshInfo(const std::string& filepath){
    std::ifstream file(filepath);
    std::string line;

    if (!file.is_open()) {
        return {};
    }

    std::vector<std::array<float, 3>> vertexPos;
    std::vector<std::array<float, 3>> vertexNormal;
    std::vector<std::array<float, 2>> textureCoords;

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
    }

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