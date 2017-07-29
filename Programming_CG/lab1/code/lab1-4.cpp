#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include "ShaderProgram.h"

const char *ShaderProgram::vertexFile = "../lab1-4_vs.glsl";
const char *ShaderProgram::fragmentFile = "../lab1-4_fs.glsl";

ShaderProgram *SP;

static void error_callback(int error, const char *description)
{
    std::cerr << description;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if ((key == GLFW_KEY_R) && action == GLFW_PRESS)
    {
        SP->ReloadShaders();
    }
    if ((key == GLFW_KEY_LEFT) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
    {
        SP->SetVertexPosition(-0.1, 0);
    }
    if ((key == GLFW_KEY_RIGHT) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
    {
        SP->SetVertexPosition(0.1, 0);
    }
    if ((key == GLFW_KEY_UP) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
    {
        SP->SetVertexPosition(0.1, 1);
    }
    if ((key == GLFW_KEY_DOWN) && ((action == GLFW_PRESS) || (action == GLFW_REPEAT)))
    {
        SP->SetVertexPosition(-0.1, 1);
    }
}

static void scroll_callback(GLFWwindow *window, double scroll_v, double scroll_h)
{
    // Update some parameter for the fragment shader here.
    SP->SetFragmentModifier(scroll_v, scroll_h);
}

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(int argc, char const *argv[])
{
    // start GL context and O/S window using the GLFW helper library

    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    GLFWwindow *window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------//
    // Set up geometry, VBO, VAO
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------//

    static const GLfloat triangle_vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    GLuint vao, vbo;
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triangle_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Shaders
    SP = new ShaderProgram();
    SP->AddFragmentShader();
    SP->AddVertexShader();
    SP->Use();

    while (!glfwWindowShouldClose(window))
    {

        //-----------------------------------------------------------------------------------------------------------------------------------------------------------//
        // Update uniform variables in your shader_program
        //-----------------------------------------------------------------------------------------------------------------------------------------------------------//

        // update other events like input handling
        glfwPollEvents();
        // clear the drawing surface
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //-----------------------------------------------------------------------------------------------------------------------------------------------------------//
        // Issue an appropriate glDraw*() command.
        //-----------------------------------------------------------------------------------------------------------------------------------------------------------//
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    // close GL context and any other GLFW resources
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
