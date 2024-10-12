#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <shader.h>

float vertices[] = {
        0.5f, 0.5f,
        -0.5f, -0.5f,
        -0.5f, 0.5f,
        0.5f, -0.5f
};

int main()
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
    {
        printf("Failed to init glfw!\n");
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLenum glewErr = glewInit();
    if (glewErr != GLEW_OK)
    {
        printf("Failed to init glew: %s\n", glewGetErrorString(glewErr));
        return -1;
    }

    uint32_t program = StrokkShaders::createProgram("assets/basic.vert", "assets/basic.frag");

    uint32_t vbo;
    glGenBuffers(1, &vbo);

    uint32_t vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}