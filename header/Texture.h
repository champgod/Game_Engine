#pragma once


class Texture{
    public:
        Texture() = default; // Constructor setup

        bool loadImage(); // Load image
        void bind(); // Bind texture
        bool isValid() const; // Is the texture valid? 

    private:
        unsigned int textureId = 0; // We want to store the ID of the texture
        int width = 0;
        int height = 0;

};