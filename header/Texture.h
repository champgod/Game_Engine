#pragma once
#include <string>
#include <OpenGL/gl3.h>

class Texture{
    public:
        Texture() = default; // Constructor setup
        ~Texture();

        Texture(const Texture&) = delete; // can't copy over for time being
        Texture& operator=(const Texture&) = delete; //can't copy over

        bool loadImage(const std::string& path); // Load image
        void bind() const; // Bind texture
        bool isValid() const; // Is the texture valid? 

        GLint getInternalFormat(int nrChannels) const;
        GLenum getFormat(int nrChannels) const;

        int getWidth() const;
        int getHeight() const;

    private:
        unsigned int textureId = 0; // We want to store the ID of the texture
        int width = 0;
        int height = 0;

};