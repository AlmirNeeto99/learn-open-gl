#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "headers/File.hpp"
#include "headers/ShaderProgram.hpp"

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main() {
    if (glfwInit() != GLFW_TRUE) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Window", NULL, NULL);

    if (!window) {
        std::cout << "Failed to initialize Window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Glad not loaded" << std::endl;
        return -1;
    }

    File vertex("../resources/vertex.vs");

    char *v = vertex.getContent();

    File frag("../resources/fragment.fs");

    char *f = frag.getContent();

    ShaderProgram program;

    program.addShader(GL_VERTEX_SHADER, v);
    program.addShader(GL_FRAGMENT_SHADER, f);

    program.link();

    glfwSetKeyCallback(window, keyCallback);

    glViewport(0, 0, 800, 600);

    glClearColor(.9f, .3f, .1f, 1.f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    program.destroy();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
