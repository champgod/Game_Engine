#pragma once
#include <fstream>
#include <sstream>
#include <string>


class OBJLoader {
    public:
        struct MeshInfo {
            std::vector<float> vertices;
            std::vector<unsigned int> indices;
        };

        static getMeshInfo(const std::string& filepath); // returns the meshinfo struct for us to read from, method should be callable by class

};