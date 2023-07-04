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

GLfloat vertices[9] = {
    .0f, .5f, .0f,
    .5f, -.5f, .0f,
    -.5f, -.5f, .0f};

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

    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLuint vao;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    glBindVertexArray(GL_NONE);

    glfwSetKeyCallback(window, keyCallback);

    glViewport(0, 0, 800, 600);

    glClearColor(.9f, .3f, .1f, 1.f);

    program.use();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();

        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    program.destroy();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
