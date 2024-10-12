#include <game.h>

#include <cstdio>

#include <shader.h>
#include <texture.h>
#include <vertexarray.h>
#include <elementbuffer.h>

std::vector<float> vertices = { /*
          x      y  |  r     g     b  |  u     v   */// Layout
        -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // Top Left
        0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,    // Bottom Right
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,   // Bottom Left
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f    // Top Right
};

float texcoords[] = {
        0.0f, 0.0f, // lower-left
        1.0f, 0.0f, // lower-right
        0.0f, 1.0f, // top-left
        1.0f, 1.0f, // top-right
};

std::vector<uint32_t> indices = {
        2, 0, 3,
        3, 1, 2
};

bool render_wireframe = false;
GLFWwindow* glfwWindow;

StrokkShader* shader = nullptr;
VertexArray* vertexArray = nullptr;

ElementBuffer* elementBuffer;

Texture* texContainer;
Texture* texFace;

int main()
{
    if (!init())
    {
        return -1;
    }

    initBuffers();

    while (!glfwWindowShouldClose(glfwWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    cleanup();
    glfwTerminate();
}


bool init()
{
    /* Initialize the library */
    if (!glfwInit())
    {
        printf("Failed to init glfw!\n");
        return false;
    }

    /* Create a windowed mode glfwWindow and its OpenGL context */
    glfwWindow = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!glfwWindow)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(glfwWindow);
    glfwSetFramebufferSizeCallback(glfwWindow, framebufferSizeCallback);
    glfwSetKeyCallback(glfwWindow, inputCallback);

    GLenum glewErr = glewInit();
    if (glewErr != GLEW_OK)
    {
        printf("Failed to init glew: %s\n", glewGetErrorString(glewErr));
        return false;
    }

    /* Make the glfwWindow's context current */
    glfwMakeContextCurrent(glfwWindow);

    return true;
}

void initBuffers()
{
    shader = new StrokkShader("assets/basic.vert", "assets/basic.frag");

    {
        VertexArrayBuilder<float> builder;
        builder.addAttribute(2);
        builder.addAttribute(3);
        builder.addAttribute(2);
        vertexArray = builder.build(&vertices, GL_STATIC_DRAW);
    }

    // Element buffer
    elementBuffer = new ElementBuffer(&indices);

    // Textures
    texContainer = new Texture("assets/textures/container.jpg");
    texFace = new Texture("assets/textures/awesomeface.png", true);

    shader->uniform("texture1", 0);
    shader->uniform("texture2", 1);
}

void render()
{
    if (render_wireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    texContainer->bindActive(0);
    texFace->bindActive(1);

    shader->bind();
    vertexArray->bindVertexArray();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void cleanup()
{
    delete shader;

    delete texContainer;
    delete texFace;

    delete vertexArray;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        render_wireframe = !render_wireframe;
    }
}