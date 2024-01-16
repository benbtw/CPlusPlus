#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <Input.h>

using namespace mcClone;

#define windowWidth 1280
#define windowHeight 720
#define windowTitle "Minecraft Clone"

GLFWwindow *init_window(GLFWwindow *window)
{
    if (!glfwInit())
    {
        std::cout << "Failed to init GLFW\n";
        return GLFW_FALSE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return GLFW_FALSE;
    }

    int width, height;
    int channels;
    unsigned char *pixels = stbi_load("C:/Users/newmi/OneDrive/Pictures/mcIcon.png", &width, &height, &channels, 4);

    GLFWimage icon[1];
    icon[0].width = width;
    icon[0].height = height;
    icon[0].pixels = pixels;
    glfwSetWindowIcon(window, 1, icon);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // v-sync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init Glad\n";
        return GLFW_FALSE;
    }

    return window;
}

int main()
{
    GLFWwindow *window = init_window(window);

    glfwSetKeyCallback(window, Input::keyCallback);
    glfwSetMouseButtonCallback(window, Input::mouseButtonCallback);
    glViewport(0, 0, windowWidth, windowHeight);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(250.0f / 255.0f, 119.0f / 255.0f, 110.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (Input::isKeyDown(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}