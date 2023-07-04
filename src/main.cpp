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

GLfloat vertices[] = {
    0.5f, 0.5f, 0.0f,    // top right
    0.5f, -0.5f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f, 0.5f, 0.0f    // top left
};

GLuint indices[] = {
    0, 1, 3, 1, 2, 3};

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

    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(GL_NONE);

    glfwSetKeyCallback(window, keyCallback);

    glViewport(0, 0, 800, 600);

    glClearColor(.0f, .0f, .0f, 1.f);

    program.use();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();

        glBindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    program.destroy();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
