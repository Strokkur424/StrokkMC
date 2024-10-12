#include <elementbuffer.h>
#include <cstdio>

ElementBuffer::ElementBuffer(std::vector<uint32_t>* indices)
{
    glGenBuffers(1, &m_ebo);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices->data()) * indices->size(), indices->data(), GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
    // TODO: Delete the EBO
}

void ElementBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}