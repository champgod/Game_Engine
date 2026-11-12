#pragma once

#include <string>
#include <vector>


class OBJLoader {
    public:
        struct MeshInfo {
            std::vector<float> vertices;
            std::vector<unsigned int> indices;
        };

        static MeshInfo getMeshInfo(const std::string& filepath); // returns the meshinfo struct for us to read from, method should be callable by class

};