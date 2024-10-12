#include <cstdio>

#include <texture.h>
#include <vendor/stb_image.h>

using namespace Textures;

uint32_t Textures::create(const char* path)
{
    return Textures::create(path, DEFAULT_FLIP_TEXTURE, DEFAULT_ALPHA_CHANNEL, DEFAULT_TEXTURE_WRAP, DEFAULT_MIN_FILTER, DEFAULT_MAG_FILTER);
}

uint32_t Textures::create(const char* path, bool flipTexture, bool alpha, GLenum textureWrap, GLenum minFilter, GLenum magFilter)
{
    uint32_t texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrap);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flipTexture);

    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (!data)
    {
        fprintf(stderr, "Could not load texture from path '%s'\n", path);
        return 0;
    }

    GLenum format = alpha ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    return texture;
}


Texture::Texture(uint32_t texture)
{
    m_glTexture = texture;
    select();
}

Texture::Texture(const char* path, bool alpha, bool flipTexture)
{
    m_glTexture = create(path, flipTexture, alpha, DEFAULT_TEXTURE_WRAP, DEFAULT_MIN_FILTER, DEFAULT_MAG_FILTER);
}

Texture::Texture(const char* path, GLenum textureWrap, GLenum minFilter, GLenum magFilter)
{
    m_glTexture = create(path, DEFAULT_FLIP_TEXTURE, DEFAULT_ALPHA_CHANNEL, textureWrap, minFilter, magFilter);
}

Texture::Texture(const char* path, bool alpha, bool flipTexture, GLenum textureWrap, GLenum minFilter, GLenum magFilter)
{
    m_glTexture = create(path, flipTexture, alpha, textureWrap, minFilter, magFilter);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_glTexture);
}

void Texture::select() const
{
    glBindTexture(GL_TEXTURE_2D, m_glTexture);
}

void Texture::bindActive(uint32_t texLoc) const {
    glActiveTexture(GL_TEXTURE0 + texLoc);
    glBindTexture(GL_TEXTURE_2D, m_glTexture);
}

