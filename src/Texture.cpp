#include "Texture.h"

Texture::Texture(){
}

Texture::~Texture(){
    if(textureId != 0){
        glDeleteTextures(1, &textureId);
    }
}


bool Texture::loadImage(const std::string& path){
    unsigned char *data = stbi_load(path.c_str(), &width, &height, 3, 0);
}

void Texture::bind() const{
    glBindTexture(GL_TEXTURE_2D, textureId);
}

bool Texture::isValid() const{
    return textureId != 0;
}

int Texture::getWidth() const{
    return width;
}

int Texture::getHeight() const{
    return height;
}