#include <GLFW/glfw3.h>

class IRenderer
{

private:
    GLFWwindow *window = nullptr;

private:
    virtual void init() = 0;

public:
    // This class is not supposed to be constructed without polymorphism.
    // Thus, I am assuming init() to be safe to be called in the constructor.
    IRenderer(GLFWwindow *window)
    {
        this->window = window;
        init();
    }

    virtual double render() = 0;

    virtual ~IRenderer() = 0;

};