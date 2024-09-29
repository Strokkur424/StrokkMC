#include <render/abstract_renderer.h>

class OpenGlRenderer : public IRenderer
{

private:
    void init() override
    {

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