#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(void)
{
    // initalize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << '\n';
        return -1;
    }

    // set OpenGL version hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a window
    GLFWwindow *window = glfwCreateWindow(800, 600, "Space Game", NULL, NULL);

    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << '\n';
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // intialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << '\n';
        return -1;
    }

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // input ...

        // rendering
        glClearColor(0.0f,0.0f,0.2f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);

        // swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // cleanup
    glfwTerminate();
    return 0;
}
