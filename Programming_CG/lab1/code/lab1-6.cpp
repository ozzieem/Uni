// GL Extension Wrangler
#include <GL/glew.h>
#include <cmath>
// http://www.glfw.org/faq.html#what-is-glfw
//OpenGL doesn't have a way of creating window, this does it in an OS-independent way
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include "ShaderProgram.h"

const char *ShaderProgram::vertexFile = "../lab1-6_vs.glsl";
const char *ShaderProgram::fragmentFile = "../lab1-6_fs.glsl";
float viewFz = 2.0;
float viewFx = 0.0;
float viewFy = 0.0;

ShaderProgram *SP;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
// You can store the rotation angles here, for example
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
float gRot[2] = {0.0, 0.0};
float dAng = 0.1;

void MUL_4x4(float (*C)[4], const float (*A)[4], const float (*B)[4])
{

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      C[j][i] = A[j][0] * B[0][i] + A[j][1] * B[1][i] + A[j][2] * B[2][i] + A[j][3] * B[3][i];
  //computes C = A x B
}

void invertMatrix(float (*C)[4], const float (*A)[4])
{
  // computes C = A^(-1) for a transformation matrix
  // still calculates if determinant is 0

  C[0][0] = A[1][1] * A[2][2] * A[3][3] -
            A[1][1] * A[2][3] * A[3][2] -
            A[2][1] * A[1][2] * A[3][3] +
            A[2][1] * A[1][3] * A[3][2] +
            A[3][1] * A[1][2] * A[2][3] -
            A[3][1] * A[1][3] * A[2][2];

  C[1][0] = -A[1][0] * A[2][2] * A[3][3] +
            A[1][0] * A[2][3] * A[3][2] +
            A[2][0] * A[1][2] * A[3][3] -
            A[2][0] * A[1][3] * A[3][2] -
            A[3][0] * A[1][2] * A[2][3] +
            A[3][0] * A[1][3] * A[2][2];

  C[2][0] = A[1][0] * A[2][1] * A[3][3] -
            A[1][0] * A[2][3] * A[3][1] -
            A[2][0] * A[1][1] * A[3][3] +
            A[2][0] * A[1][3] * A[3][1] +
            A[3][0] * A[1][1] * A[2][3] -
            A[3][0] * A[1][3] * A[2][1];

  C[3][0] = -A[1][0] * A[2][1] * A[3][2] +
            A[1][0] * A[2][2] * A[3][1] +
            A[2][0] * A[1][1] * A[3][2] -
            A[2][0] * A[1][2] * A[3][1] -
            A[3][0] * A[1][1] * A[2][2] +
            A[3][0] * A[1][2] * A[2][1];

  C[0][1] = -A[0][1] * A[2][2] * A[3][3] +
            A[0][1] * A[2][3] * A[3][2] +
            A[2][1] * A[0][2] * A[3][3] -
            A[2][1] * A[0][3] * A[3][2] -
            A[3][1] * A[0][2] * A[2][3] +
            A[3][1] * A[0][3] * A[2][2];

  C[1][1] = A[0][0] * A[2][2] * A[3][3] -
            A[0][0] * A[2][3] * A[3][2] -
            A[2][0] * A[0][2] * A[3][3] +
            A[2][0] * A[0][3] * A[3][2] +
            A[3][0] * A[0][2] * A[2][3] -
            A[3][0] * A[0][3] * A[2][2];

  C[2][1] = -A[0][0] * A[2][1] * A[3][3] +
            A[0][0] * A[2][3] * A[3][1] +
            A[2][0] * A[0][1] * A[3][3] -
            A[2][0] * A[0][3] * A[3][1] -
            A[3][0] * A[0][1] * A[2][3] +
            A[3][0] * A[0][3] * A[2][1];

  C[3][1] = A[0][0] * A[2][1] * A[3][2] -
            A[0][0] * A[2][2] * A[3][1] -
            A[2][0] * A[0][1] * A[3][2] +
            A[2][0] * A[0][2] * A[3][1] +
            A[3][0] * A[0][1] * A[2][2] -
            A[3][0] * A[0][2] * A[2][1];

  C[0][2] = A[0][1] * A[1][2] * A[3][3] -
            A[0][1] * A[1][3] * A[3][2] -
            A[1][1] * A[0][2] * A[3][3] +
            A[1][1] * A[0][3] * A[3][2] +
            A[3][1] * A[0][2] * A[1][3] -
            A[3][1] * A[0][3] * A[1][2];

  C[1][2] = -A[0][0] * A[1][2] * A[3][3] +
            A[0][0] * A[1][3] * A[3][2] +
            A[1][0] * A[0][2] * A[3][3] -
            A[1][0] * A[0][3] * A[3][2] -
            A[3][0] * A[0][2] * A[1][3] +
            A[3][0] * A[0][3] * A[1][2];

  C[2][2] = A[0][0] * A[1][1] * A[3][3] -
            A[0][0] * A[1][3] * A[3][1] -
            A[1][0] * A[0][1] * A[3][3] +
            A[1][0] * A[0][3] * A[3][1] +
            A[3][0] * A[0][1] * A[1][3] -
            A[3][0] * A[0][3] * A[1][1];

  C[3][2] = -A[0][0] * A[1][1] * A[3][2] +
            A[0][0] * A[1][2] * A[3][1] +
            A[1][0] * A[0][1] * A[3][2] -
            A[1][0] * A[0][2] * A[3][1] -
            A[3][0] * A[0][1] * A[1][2] +
            A[3][0] * A[0][2] * A[1][1];

  C[0][3] = -A[0][1] * A[1][2] * A[2][3] +
            A[0][1] * A[1][3] * A[2][2] +
            A[1][1] * A[0][2] * A[2][3] -
            A[1][1] * A[0][3] * A[2][2] -
            A[2][1] * A[0][2] * A[1][3] +
            A[2][1] * A[0][3] * A[1][2];

  C[1][3] = A[0][0] * A[1][2] * A[2][3] -
            A[0][0] * A[1][3] * A[2][2] -
            A[1][0] * A[0][2] * A[2][3] +
            A[1][0] * A[0][3] * A[2][2] +
            A[2][0] * A[0][2] * A[1][3] -
            A[2][0] * A[0][3] * A[1][2];

  C[2][3] = -A[0][0] * A[1][1] * A[2][3] +
            A[0][0] * A[1][3] * A[2][1] +
            A[1][0] * A[0][1] * A[2][3] -
            A[1][0] * A[0][3] * A[2][1] -
            A[2][0] * A[0][1] * A[1][3] +
            A[2][0] * A[0][3] * A[1][1];

  C[3][3] = A[0][0] * A[1][1] * A[2][2] -
            A[0][0] * A[1][2] * A[2][1] -
            A[1][0] * A[0][1] * A[2][2] +
            A[1][0] * A[0][2] * A[2][1] +
            A[2][0] * A[0][1] * A[1][2] -
            A[2][0] * A[0][2] * A[1][1];
}

static void error_callback(int error, const char *description)
{
  std::cerr << description;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  if ((key == GLFW_KEY_R) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
  {
    viewFz += 0.1;
  }
  if ((key == GLFW_KEY_T) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
  {
    viewFz -= 0.1;
  }

  if ((key == GLFW_KEY_F) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
  {
    viewFy += 0.1;
  }
  if ((key == GLFW_KEY_G) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
  {
    viewFy -= 0.1;
  }

  if ((key == GLFW_KEY_V) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
  {
    viewFx += 0.1;
  }
  if ((key == GLFW_KEY_B) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
  {
    viewFx -= 0.1;
  }

  //-----------------------------------------------------------------------------------------------------------------------------------------------------------//
  // Update rotation angle here, for example
  //-----------------------------------------------------------------------------------------------------------------------------------------------------------//

  if ((key == GLFW_KEY_RIGHT) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
    gRot[1] += dAng;
  if ((key == GLFW_KEY_LEFT) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
    gRot[1] -= dAng;
  if ((key == GLFW_KEY_UP) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
    gRot[0] -= dAng;
  if ((key == GLFW_KEY_DOWN) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
    gRot[0] += dAng;
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

  int w_height = 600;
  int w_width = 800;

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

  glBindVertexArray(vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  float n = 1.0;
  float f = 100.0;
  float a = -(f + n) / (f - n);
  float b = -(2 * f * n) / (f - n);

  while (!glfwWindowShouldClose(window))
  {
    glfwGetFramebufferSize(window, &w_width, &w_height); //you might need this for correcting the aspect ratio

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------//
    // Define the projection matrix, rotation matrices, model matrix, etc. The variable names and code structure is a simple suggestion, you may improve on it!
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------//
    GLfloat rotate_y[4][4] = {{cos(gRot[1]), 0, sin(gRot[1]), 0},
                              {0, 1.0, 0, 0},
                              {-sin(gRot[1]), 0, cos(gRot[1]), 0},
                              {0, 0, 0, 1.0}};

    GLfloat rotate_x[4][4] = {{1.0, 0, 0, 0},
                              {0, cos(gRot[0]), -sin(gRot[0]), 0},
                              {0, sin(gRot[0]), cos(gRot[0]), 0},
                              {0, 0, 0, 1.0}};
    // 1. Set up model matrix
    GLfloat modelMatrix[4][4];
    MUL_4x4(modelMatrix, rotate_x, rotate_y);

    // 2. Set up view matrix
    GLfloat viewMatrix[4][4] = {{1.0, 0, 0, 0},
                                {0, 1.0, 0, 0},
                                {0, 0, 1.0, viewFz},
                                {0, 0, 0, 1.0}};

    GLfloat inverseViewMatrix[4][4];
    invertMatrix(inverseViewMatrix, viewMatrix);

    // 3. Set up projection matrix
    GLfloat projectionMatrix[4][4] = {{float(w_height) / float(w_width), 0, 0, 0},
                                      {0, 1.0, 0, 0},
                                      {0, 0, a, b},
                                      {0, 0, -1.0, 0}};
    // 4. Combine them
    GLfloat modelViewMatrix[4][4];
    MUL_4x4(modelViewMatrix, inverseViewMatrix, modelMatrix);
    GLfloat modelViewProjectionMatrix[4][4];
    MUL_4x4(modelViewProjectionMatrix, projectionMatrix, modelViewMatrix);

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------//
    // Send your modelViewProjection matrix to your vertex shader as a uniform varable
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------//
    GLint uniLoc = glGetUniformLocation(SP->program, "mvp");
    glUniformMatrix4fv(uniLoc, GL_TRUE, GL_TRUE, *modelViewProjectionMatrix);

    // update other events like input handling
    glfwPollEvents();

    // clear the drawing surface
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // indexed draw call
    glDrawRangeElements(GL_TRIANGLES, 0, 19, sizeof(indices) / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

    glfwSwapBuffers(window);
  }
  // close GL context and any other GLFW resources
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
