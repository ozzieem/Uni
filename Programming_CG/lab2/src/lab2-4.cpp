#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "ShaderProgram.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

const char *ShaderProgram::vertexFile = "../lab2_vs.glsl";
const char *ShaderProgram::fragmentFile = "../lab2-4_fs.glsl";

ShaderProgram *SP;

float viewFz = 2.0;
float viewFx = 0.0;
float viewFy = 0.0;

float gRot[2] = {0.0, 0.0};
float dAng = 0.1;

glm::vec4 lightCol[4] = {glm::vec4(1.0, 1.0, 1.0, 1.0),
                         glm::vec4(1.0, 1.0, 1.0, 1.0),
                         glm::vec4(1.0, 1.0, 1.0, 1.0),
                         glm::vec4(1.0, 1.0, 1.0, 1.0)};

glm::vec4 lightPos[4] = {glm::vec4(0.0, 0.0, 1.0, 0.0),
                         glm::vec4(0.0, 1.0, 1.0, 0.0),
                         glm::vec4(1.0, 0.0, 1.0, 0.0),
                         glm::vec4(-1.0, 0.0, 1.0, 0.0)};

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
  if ((key == GLFW_KEY_W) && ((action == GLFW_PRESS) || action == GLFW_REPEAT))
    SP->ReloadShaders();
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
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  GLFWwindow *window = glfwCreateWindow(w_width, w_height, "Hello Bunny", NULL, NULL);
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

  std::string inputfile = "../../common/data/bunny.obj";
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string err;
  int flags = 0; // see load_flags_t enum for more information.

  // Load the object
  bool ret = tinyobj::LoadObj(shapes, materials, err, inputfile.c_str(), 0, flags);

  // Check for errors
  if (!err.empty())
  { // `err` may contain warning message.
    std::cerr << err << std::endl;
  }

  if (!ret)
  {
    exit(1);
  }
  else
  {
    std::cout << "Loaded " << inputfile
              << " ("
              << shapes.size() << " shapes"
              << ")"
              << "\n";
  }

  std::cout << "shapes indices: " << shapes[0].mesh.indices.size() << '\n';
  std::cout << "shapes normals: " << shapes[0].mesh.normals.size() << '\n';
  std::cout << "shapes vertices: " << shapes[0].mesh.positions.size() << '\n';

  // Populate your VBO with shapes[0].mesh.positions and shapes[0].mesh.normals
  // ...
  // Populate your EBO with shapes[0].mesh.indices
  // ...

  GLuint vao, vbo[2], ebo;

  // ------ VAO -----
  glGenVertexArrays(1, &vao); // Create new VAO
  // Binded VAO will store connections between VBOs and attributes
  glBindVertexArray(vao);

  // ------ VBO ------
  glGenBuffers(2, vbo);                  // Create new VBO
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // Bind as current vertex buffer
  // initialize vertex buffer, fill it with data
  glBufferData(GL_ARRAY_BUFFER, shapes[0].mesh.positions.size() * sizeof(GLfloat), &shapes[0].mesh.positions[0], GL_STATIC_DRAW);
  // indicate how vertex attribute 0 should interpret data in connected VBO
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  // indicate that current VBO should be used with vertex attr with index 0
  glEnableVertexAttribArray(0);

  // ------ VBO Normals ------
  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // Bind as current vertex buffer
  // initialize vertex buffer, fill it with data
  glBufferData(GL_ARRAY_BUFFER, shapes[0].mesh.normals.size() * sizeof(GLfloat), &shapes[0].mesh.normals[0], GL_STATIC_DRAW);
  // indicate that current VBO should be used with vertex attr with index 1
  // indicate how vertex attribute 1 should interpret data in connected VBO
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);

  // ------- EBO -------
  glGenBuffers(1, &ebo); // create new EBO buffer to store indices
  // binds buffer to corresponding target
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  // initialize index buffer, fill it with data
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapes[0].mesh.indices.size() * sizeof(GLuint), &shapes[0].mesh.indices[0], GL_STATIC_DRAW);

  // reset bindings for VAO, VBO and EBO
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Shaders
  SP = new ShaderProgram();
  SP->AddVertexShader();
  SP->AddFragmentShader();
  SP->Use();

  // Draw
  glBindVertexArray(vao);
  // bind index buffer if you want to render indexed data
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  std::cout << "Starting loop\n";
  while (!glfwWindowShouldClose(window))
  {
    //you might need this for correcting the aspect ratio
    glfwGetFramebufferSize(window, &w_width, &w_height);

    // Define the projection matrix, rotation matrices, model matrix, etc.

    // 1. Set up model matrix
    glm::mat4 rotxM = glm::rotate(glm::mat4(1.0f), gRot[0], glm::vec3(1.0f, 0, 0));
    glm::mat4 modelMatrix = glm::rotate(rotxM, gRot[1], glm::vec3(0, 1.0f, 0));

    // 2. Set up view matrix
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.1, viewFz));
    glm::mat4 invViewMatrix = glm::inverse(viewMatrix);

    // 2.5 Set up modelview matrix
    glm::mat4 modelViewMatrix = invViewMatrix * modelMatrix;
    
    // 3. Set up projection matrix
    glm::mat4 projMatrix = glm::perspective(0.2f, 4.0f / 3.0f, 1.0f, 100.0f);

    // 4. Combine them
    glm::mat4 MVP = projMatrix * modelViewMatrix;

    // Set up normal matrix
    glm::mat4 NM = transpose(inverse(modelViewMatrix));

    // Unifoms
    GLint uniLoc = glGetUniformLocation(SP->program, "mv");
    glUniformMatrix4fv(uniLoc, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));

    uniLoc = glGetUniformLocation(SP->program, "nm");
    glUniformMatrix4fv(uniLoc, 1, GL_FALSE, glm::value_ptr(NM));

    uniLoc = glGetUniformLocation(SP->program, "mvp");
    glUniformMatrix4fv(uniLoc, 1, GL_FALSE, glm::value_ptr(MVP));

    uniLoc = glGetUniformLocation(SP->program, "light_position");
    glUniform4fv(uniLoc, 4, glm::value_ptr(lightPos[0]));

    uniLoc = glGetUniformLocation(SP->program, "light_colour");
    glUniform4fv(uniLoc, 4, glm::value_ptr(lightCol[0]));

    // update other events like input handling
    glfwPollEvents();

    // clear the drawing surface
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // indexed draw call
    glDrawRangeElements(GL_TRIANGLES, 0, shapes[0].mesh.indices.size() - 1,
                        shapes[0].mesh.indices.size(),
                        GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
  }

  // close GL context and any other GLFW resources
  glfwTerminate();
  exit(EXIT_SUCCESS);
}