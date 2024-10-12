#ifndef STROKK_TEXTURES
#define STROKK_TEXTURES

#include <GL/glew.h>

namespace Textures
{
    const bool DEFAULT_FLIP_TEXTURE = false;
    const bool DEFAULT_ALPHA_CHANNEL = false;
    const GLenum DEFAULT_TEXTURE_WRAP = GL_REPEAT;
    const GLenum DEFAULT_MIN_FILTER = GL_LINEAR;
    const GLenum DEFAULT_MAG_FILTER = GL_LINEAR;

    uint32_t create(const char* path);
    uint32_t create(const char* path, bool flipTexture, bool alpha, GLenum textureWrap, GLenum minFilter, GLenum magFilter);
}

class Texture
{
private:
    uint32_t m_glTexture;

public:
    Texture(uint32_t texture);
    Texture(const char* path, bool alpha = false, bool flipTexture = false);
    Texture(const char* path, GLenum textureWrap, GLenum minFilter = GL_LINEAR, GLenum magFilter = GL_LINEAR);
    Texture(const char* path, bool alpha, bool flipTexture, GLenum textureWrap, GLenum minFilter, GLenum magFilter);

    ~Texture();

    void select() const;
    void bindActive(uint32_t texLoc) const;
};

#endif // STROKK_TEXTURES