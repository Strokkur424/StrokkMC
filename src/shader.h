#ifndef STROKK_SHADERS
#define STROKK_SHADERS

#include <GL/Glew.h>

class StrokkShader
{
private:
    unsigned int m_programId;

public:
    StrokkShader(const char* vertexPath, const char* fragmentPath);
    ~StrokkShader();

    void bind() const;
    unsigned int getProgram() const;

    /// Uniform methods
    // Floats
    void uniform(GLchar* name, float x);
    void uniform(GLchar* name, float x, float y);
    void uniform(GLchar* name, float x, float y, float z);
    void uniform(GLchar* name, float x, float y, float z, float w);

    void uniform(GLchar* name, int x);
    void uniform(GLchar* name, int x, int y);
    void uniform(GLchar* name, int x, int y, int z);
    void uniform(GLchar* name, int x, int y, int z, int w);
};

namespace StrokkShaders
{
    static unsigned int createShader(GLenum shaderType, const char* path);
}

#endif // STROKK_SHADERS