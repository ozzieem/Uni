#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "ShaderProgram.h"

const char *ShaderProgram::vertexFile = "../lab1-5_vs.glsl";
const char *ShaderProgram::fragmentFile = "../lab1-5_fs.glsl";

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

    GLFWwindow *window = glfwCreateWindow(640, 480, "Hello Icosahedron", NULL, NULL);
    glfwSetKeyCallback(window, key_callback);
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

    // ----------Geometry----------
    // vertices
    GLfloat t = (1.0f + sqrtf(5.0f)) * 0.25f;
    GLfloat positions[] = {
        // An icosahedron has 12 vertices
        -0.5, t, 0,
        0.5, t, 0,
        -0.5, -t, 0,
        0.5, -t, 0,
        0, -0.5, t,
        0, 0.5, t,
        0, -0.5, -t,
        0, 0.5, -t,
        t, 0, -0.5,
        t, 0, 0.5,
        -t, 0, -0.5,
        -t, 0, 0.5};

    // indices
    GLushort indices[] = {
        0, 11, 5,
        0, 5, 1,
        0, 1, 7,
        0, 7, 10,
        0, 10, 11,

        1, 5, 9,
        5, 11, 4,
        11, 10, 2,
        10, 7, 6,
        7, 1, 8,

        3, 9, 4,
        4, 4, 2,
        3, 2, 6,
        3, 6, 8,
        3, 8, 9,

        4, 9, 5,
        2, 4, 11,
        6, 2, 10,
        8, 6, 7,
        9, 8, 1};

    GLuint vao, vbo, ebo;

    // ------ VBO ------
    glGenBuffers(1, &vbo);              // Create new VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // Bind as current vertex buffer
    // initialize vertex buffer, fill it with data
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    // ------ VAO -----
    glGenVertexArrays(1, &vao); // Create new VAO
    // Binded VAO will store connections between VBOs and attributes
    glBindVertexArray(vao);
    // indicate that current VBO should be used with vertex attr with index 0
    glEnableVertexAttribArray(0);
    // indicate how vertex attribute 0 should interpret data in connected VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // ------- EBO -------
    glGenBuffers(1, &ebo); // create new EBO buffer to store indices
    // binds buffer to corresponding target
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // initialize index buffer, fill it with data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // reset bindings for VAO, VBO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // init Shaders
    SP = new ShaderProgram();
    SP->AddVertexShader();
    SP->AddFragmentShader();
    SP->Use();

    while (!glfwWindowShouldClose(window))
    {
        // update other events like input handling
        glfwPollEvents();
        // clear the drawing surface
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* After initialization VAO contains all required information 
        about which VBO corresponds to which attibute in the vertex shader, 
        and how to interpret data in VBOs. So simply bind VAO and it will 
        automatically initialize all states required for rendering.*/
        glBindVertexArray(vao);
        // bind index buffer if you want to render indexed data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        // indexed draw call
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

        glfwSwapBuffers(window);
    }

    // close GL context and any other GLFW resources
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
