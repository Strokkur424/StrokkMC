#ifndef STROKK_VERTEX_ARRAY
#define STROKK_VERTEX_ARRAY

#include <GL/glew.h>
#include <vector>

namespace UtilVertexArray
{
    struct AttribPointer
    {
        unsigned char components;
        GLenum type;
        bool normalized;
        void* offset;
    };

    template <typename T>
    GLenum asGlType();
}

class VertexArray
{
private:
    uint32_t m_vao;
    uint32_t m_vbo;

public:
    VertexArray(uint32_t vao, uint32_t vbo);
    ~VertexArray();

    void bindVertexArray();
    void bindVertexBuffer();
};

template<class T>
class VertexArrayBuilder
{
private:
    size_t m_currentOffset = 0;
    std::vector<UtilVertexArray::AttribPointer*>* m_pointers;

public:
    VertexArrayBuilder();
    ~VertexArrayBuilder();

    void addAttribute(uint16_t attribSize, bool normalized = false);
    void addAttribute(uint16_t attribSize, GLenum type, bool normalized = false);
    VertexArray* build(std::vector<T>* array, GLenum drawType = GL_STATIC_DRAW);
};

#endif // STROKK_VERTEX_ARRAY