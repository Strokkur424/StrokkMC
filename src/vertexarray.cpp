#include <vertexarray.h>
#include <typeinfo>
#include <cstring>
#include <cstdio>

using namespace std;
using namespace UtilVertexArray;

// VertexArrayBuilder definition
template<class T>
VertexArrayBuilder<T>::VertexArrayBuilder()
{
    m_pointers = new vector<AttribPointer*>();
}

template<class T>
VertexArrayBuilder<T>::~VertexArrayBuilder()
{
    // Nothing to delete; m_pointers is a reference and not necessarily owned by this class
}

template<class T>
void VertexArrayBuilder<T>::addAttribute(uint16_t attribSize, bool normalized)
{
    addAttribute(attribSize, asGlType<T>(), normalized);
}

template<class T>
void VertexArrayBuilder<T>::addAttribute(uint16_t attribSize, GLenum type, bool normalized)
{
    AttribPointer* attrib = new AttribPointer();
    attrib->components = attribSize;
    attrib->normalized = normalized;
    attrib->type = type;
    attrib->offset = (void*) m_currentOffset;

    m_currentOffset += sizeof(attrib->type) * attribSize;
    m_pointers->push_back(attrib);
}

template<class T>
VertexArray* VertexArrayBuilder<T>::build(std::vector<T>* array, GLenum drawType)
{
    uint32_t vao, vbo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T) * array->size(), array->data(), drawType);

    for (int i = 0; i < m_pointers->size(); i++)
    {
        AttribPointer* attrib = m_pointers->at(i);
        glVertexAttribPointer(i, attrib->components, attrib->type, attrib->normalized, m_currentOffset, attrib->offset);
        glEnableVertexAttribArray(i);
    }

    return new VertexArray(vao, vbo);
}

// VertexArray class definition
VertexArray::VertexArray(uint32_t vao, uint32_t vbo)
{
    m_vao = vao;
    m_vbo = vbo;
}

VertexArray::~VertexArray()
{
    // TODO: Delete VAO and VBO
}

void VertexArray::bindVertexArray()
{
    glBindVertexArray(m_vao);
}

void VertexArray::bindVertexBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}


template<class T>
GLenum UtilVertexArray::asGlType()
{
    const char* type = typeid(T).name();

    if (strcmp(type, "float"))
    {
        return GL_FLOAT;
    }

    if (strcmp(type, "double"))
    {
        return GL_DOUBLE;
    }

    if (strcmp(type, "int"))
    {
        return GL_INT;
    }

    fprintf(stderr, "Could not get GL type from '%s'\n", type);
    return 0;
}


template class VertexArrayBuilder<float>;