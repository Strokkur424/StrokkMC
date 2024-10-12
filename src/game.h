#include <GL/glew.h>
#include <GLFW/glfw3.h>

bool init();
void initBuffers();
void render();
void cleanup();

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);