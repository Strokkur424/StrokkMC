#include <shader.h>
#include <files.h>
#include <cstdio>
#include <cstdlib>

unsigned int StrokkShaders::createProgram(const char *vertexPath, const char *fragmentPath)
{
    unsigned int vertexShader = StrokkShaders::createShader(GL_VERTEX_SHADER, vertexPath);
    unsigned int fragmentShader = StrokkShaders::createShader(GL_FRAGMENT_SHADER, fragmentPath);

    if (vertexShader == 0)
    {
        fprintf(stderr, "Could not create program because the vertex shader had an exception!\n");
        return 0;
    }

    if (fragmentShader == 0)
    {
        fprintf(stderr, "Could not create program because the fragment shader had an exception!\n");
        return 0;
    }

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        fprintf(stderr, "Could not create program from '%s' and '%s': \n%s\n", vertexPath, fragmentPath, infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (!success)
    {
        return 0;
    }

    return program;
}

unsigned int StrokkShaders::createShader(GLenum shaderType, const char *path)
{
    unsigned int shader;
    shader = glCreateShader(shaderType);
    char *src = File::readAllText(path);

    if (src == nullptr) {
        return 0;
    }

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        fprintf(stderr, "Could not compile shader source code for '%s': \n%s\n", path, infoLog);
        printf("Shader source: \n%s\n", src);
        delete[] src;
        return 0;
    }

    free(src);
    return shader;
}

