#include <shader.h>
#include <files.h>
#include <cstdio>
#include <cstdlib>

StrokkShader::StrokkShader(const char* vertexPath, const char* fragmentPath)
{
    unsigned int vertexShader = StrokkShaders::createShader(GL_VERTEX_SHADER, vertexPath);
    unsigned int fragmentShader = StrokkShaders::createShader(GL_FRAGMENT_SHADER, fragmentPath);

    if (vertexShader == 0)
    {
        fprintf(stderr, "Could not create program because the vertex shader had an exception!\n");
        return;
    }

    if (fragmentShader == 0)
    {
        fprintf(stderr, "Could not create program because the fragment shader had an exception!\n");
        return;
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
        return;
    }

    m_programId = program;
    bind();
}

StrokkShader::~StrokkShader()
{
    glDeleteProgram(m_programId);
}


void StrokkShader::bind() const
{
    glUseProgram(m_programId);
}

unsigned int StrokkShader::getProgram() const
{
    return m_programId;
}

unsigned int StrokkShaders::createShader(GLenum shaderType, const char* path)
{
    unsigned int shader;
    shader = glCreateShader(shaderType);
    char* src = File::readAllText(path);

    if (src == nullptr)
    {
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

// Uniforms:
void StrokkShader::uniform(GLchar* name, float x)
{
    int location = glGetUniformLocation(getProgram(), name);
    bind();
    glUniform1f(location, x);
}

void StrokkShader::uniform(GLchar* name, float x, float y)
{
    int location = glGetUniformLocation(getProgram(), name);
    bind();
    glUniform2f(location, x, y);
}

void StrokkShader::uniform(GLchar* name, float x, float y, float z)
{
    int location = glGetUniformLocation(getProgram(), name);
    bind();
    glUniform3f(location, x, y, z);
}

void StrokkShader::uniform(GLchar* name, float x, float y, float z, float w)
{
    int location = glGetUniformLocation(getProgram(), name);
    bind();
    glUniform4f(location, x, y, z, w);
}

void StrokkShader::uniform(GLchar* name, int x)
{
    int location = glGetUniformLocation(getProgram(), name);
    bind();
    glUniform1i(location, x);
}

void StrokkShader::uniform(GLchar* name, int x, int y)
{
    int location = glGetUniformLocation(getProgram(), name);
    bind();
    glUniform2i(location, x, y);
}

void StrokkShader::uniform(GLchar* name, int x, int y, int z)
{
    int location = glGetUniformLocation(getProgram(), name);
    bind();
    glUniform3i(location, x, y, z);
}

void StrokkShader::uniform(GLchar* name, int x, int y, int z, int w)
{
    int location = glGetUniformLocation(getProgram(), name);
    bind();
    glUniform4i(location, x, y, z, w);
}
