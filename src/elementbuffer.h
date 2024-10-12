#ifndef STROKK_ELEMENT_BUFFER
#define STROKK_ELEMENT_BUFFER

#include <GL/glew.h>
#include <vector>

class ElementBuffer
{

private:
    uint32_t m_ebo;

public:
    ElementBuffer(std::vector<uint32_t>* indices);
    ~ElementBuffer();

    void bind();
};


#endif // STROKK_ELEMENT_BUFFER