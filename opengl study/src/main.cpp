#include <stdlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

int main()
{
    GLFWwindow *window;

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to init GLFW\n");
        return -1;
    }

    window = glfwCreateWindow(1024, 768, "GLFW/GLEW", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW Window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}