#ifndef StrokkShadersSrc
#define StrokkShadersSrc

#include <GL/Glew.h>

namespace StrokkShaders
{
    unsigned int createProgram(const char* vertexPath, const char* fragmentPath);
    static unsigned int createShader(GLenum shaderType, const char* path);
}

#endif // StrokkShadersSrc