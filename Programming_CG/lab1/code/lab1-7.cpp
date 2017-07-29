#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <cstdlib>
#include <iostream>
#include "ShaderProgram.h"

const char *ShaderProgram::vertexFile = "../lab1-7_vs.glsl";
const char *ShaderProgram::fragmentFile = "../lab1-7_fs.glsl";

ShaderProgram *SP;

float viewFz = 2.0;
float viewFx = 0.0;
float viewFy = 0.0;

float gRot[2] = {0.0, 0.0};
float dAng = 0.1;

static void error_callback(int error, const char *description)
{
  std::cerr << description;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  if ((key == GLFW_KEY_R) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
    viewFz += 0.1;
  if ((key == GLFW_KEY_T) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
    viewFz -= 0.1;
  if ((key == GLFW_KEY_F) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
    viewFy += 0.1;
  if ((key == GLFW_KEY_G) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
    viewFy -= 0.1;
  if ((key == GLFW_KEY_V) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
    viewFx += 0.1;
  if ((key == GLFW_KEY_B) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
    viewFx -= 0.1;

  //-----------------------------------------------------------------------------------------------------------------------------------------------------------//
  // Update rotation angle here, for example
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------//

  if ((key == GLFW_KEY_UP) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
    gRot[0] -= dAng;
  if ((key == GLFW_KEY_DOWN) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
    gRot[0] += dAng;
  if ((key == GLFW_KEY_RIGHT) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
    gRot[1] += dAng;
  if ((key == GLFW_KEY_LEFT) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
    gRot[1] -= dAng;
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

  int w_height = 600;
  int w_width = 800;

  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_VERSION_MINOR, 3);

  GLFWwindow *window = glfwCreateWindow(w_width, w_height, "Hello Icosahedron", NULL, NULL);
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

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS);    // depth-testing interprets a smaller value as "closer"

  //-----------------------------------------------------------------------------------------------------------------------------------------------------------//
  // Set up geometry, VBO, EBO, VAO
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
      3, 4, 2,
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

  // Shaders
  SP = new ShaderProgram();
  SP->AddFragmentShader();
  SP->AddVertexShader();
  SP->Use();

  // Draw
  glBindVertexArray(vao);
  // bind index buffer if you want to render indexed data
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  while (!glfwWindowShouldClose(window))
  {
    //you might need this for correcting the aspect ratio
    glfwGetFramebufferSize(window, &w_width, &w_height);

    // Define the projection matrix, rotation matrices, model matrix, etc.

    // 1. Set up model matrix
    glm::mat4 rotxM = glm::rotate(glm::mat4(1.0f), gRot[0], glm::vec3(1.0f, 0, 0));
    glm::mat4 modelMatrix = glm::rotate(rotxM, gRot[1], glm::vec3(0, 1.0f, 0));

    // 2. Set up view matrix
    glm::mat4 viewM = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, viewFz));
    glm::mat4 viewMatrix = glm::inverse(viewM);

    // 3. Set up projection matrix
    glm::mat4 projMatrix = glm::perspective(1.0f, 4.0f / 3.0f, 1.0f, 100.0f);

    // 4. Combine them
    glm::mat4 MVP = projMatrix * viewMatrix * modelMatrix;

    GLint uniLoc = glGetUniformLocation(SP->program, "mvp");
    glUniformMatrix4fv(uniLoc, 1, GL_FALSE, glm::value_ptr(MVP));

    // update other events like input handling
    glfwPollEvents();

    // clear the drawing surface
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // indexed draw call
    glDrawRangeElements(GL_TRIANGLES, 0, 19,
                        sizeof(indices) / sizeof(GLushort),
                        GL_UNSIGNED_SHORT, 0);

    glfwSwapBuffers(window);
  }

  // close GL context and any other GLFW resources
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
