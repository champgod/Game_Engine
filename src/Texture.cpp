#include "Texture.h"
#include "stb_image.h"

Texture::~Texture(){
    if(textureId != 0){
        glDeleteTextures(1, &textureId);
    }
}


bool Texture::loadImage(const std::string& path){
    int nWidth = 0;
    int nHeight = 0;
    int nrChannels = 0;
    unsigned char *data = stbi_load(path.c_str(), &nWidth, &nHeight, &nrChannels, 0);

    if (data == nullptr){
        return false;
    }

    GLint internalFormat = getInternalFormat(nrChannels);
    GLenum format = getFormat(nrChannels);

    if (internalFormat == 0 || format == 0) {
        stbi_image_free(data);
        return false;
    }

    
    if (textureId != 0) {
        glDeleteTextures(1, &textureId);
        textureId = 0;
    }

    glGenTextures(1, &textureId);
    bind();
    // set the texture wrapping/filtering options (on the currently bound texture object). fully snatched this from learnopengl
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// repeats the texture in a horizontal direction
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  // repeats the texture in a vertical direction
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // when far away the texture looks smoother
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // when close the texture looks more detailed

    GLint previousAlignment;
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &previousAlignment);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, nWidth, nHeight, 0, format, GL_UNSIGNED_BYTE, data);
    glPixelStorei(GL_UNPACK_ALIGNMENT, previousAlignment);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    width = nWidth;
    height = nHeight;

    return true;
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

GLint Texture::getInternalFormat(int nrChannels) const{
    if (nrChannels == 3){
        return GL_RGB8;
    }
    if (nrChannels == 4){
        return GL_RGBA8;
    }
    return 0; // no supported type
}

GLenum Texture::getFormat(int nrChannels) const{
    if (nrChannels == 3) {
        return GL_RGB;
    }
    else if (nrChannels == 4) {
        return GL_RGBA;
    }
    return 0; // no supported type
}