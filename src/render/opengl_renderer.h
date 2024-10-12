#include <render/abstract_renderer.h>
#include <GL/gl.h>



class OpenGlRenderer : public IRenderer
{

private:
    unsigned int vbo;

private:
    void init() override
    {

        glDrawBuffer(GL_TRIANGLES);
    }

public:
    double render() override
    {
        return 0;
    }

    ~OpenGlRenderer() override
    {
        // cleanup
    }

};