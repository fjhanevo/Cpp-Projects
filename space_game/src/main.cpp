#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <strings.h>
#include <math.h>

#include "shader.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);

int main()
{
    // first we init the window
    glfwInit();
    // version stuff
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // create window
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW Window\n";
        glfwTerminate();    // KILL HIM
        return -1;
    }

    // make the window on a single thread, whatever that means
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // load all opengl function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to intialize GLAD\n";
        return -1;
    }
    // ------- Shader building -------
    Shader shader{"shaders/vertex.v.glsl", "shaders/fragment.f.glsl"}; 
    // ------- Vertex setup -------
    float vertices[] = {
        // positions        // colors
        0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    // bottom right
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,    // bottom left
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,     // top
        -0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f
    };

    unsigned int indices[] = {
        0,1,3,
        1,2,3
    };


    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ------- Render Loop -------
    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        // draw background first
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //activate shader
        shader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();

    return 0; 
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
/* callback function to resize the screen if it's changed */
    glViewport(0,0,width,height);
}

void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || 
        glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true);

}
