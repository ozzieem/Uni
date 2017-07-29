#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "readfile.hpp"
#include <vector>

class ShaderProgram
{
  public:
    static const char *VSFile;
    static const char *FSFile;
    static const char *TCSFile;
    static const char *TESFile;

    GLuint program;

    GLuint vertexShader;
    GLuint fragmentShader;

    GLfloat PosOffset[];
    GLfloat scrollOffset;

    ShaderProgram()
    {
        program = glCreateProgram();
        PosOffset[0] = 0.0;
        PosOffset[1] = 0.0;
        scrollOffset = 0.0;
    }

    void Use()
    {
        glUseProgram(this->program);
        std::cout << "Shaderprogram installed" << '\n';
    }

    void AddVertexShader()
    {
        vertexShader = CreateShader(VSFile, GL_VERTEX_SHADER);
        AddShader(vertexShader, "VS");
    }

    void AddFragmentShader()
    {
        fragmentShader = CreateShader(FSFile, GL_FRAGMENT_SHADER);
        AddShader(fragmentShader, "FS");
    }

    GLuint CreateShader(const char *file, const int type)
    {
        std::string shader_str = readFile(file);
        const char *shader_src = shader_str.c_str();
        GLuint s = glCreateShader(type);
        glShaderSource(s, 1, &shader_src, NULL);
        return s;
    }

    void AddShader(GLuint s, std::string shaderType)
    {
        glCompileShader(s);
        CheckCompilerError(s, shaderType);
        glAttachShader(this->program, s);
        glLinkProgram(this->program);
        glDeleteShader(s);
    }

    void CheckCompilerError(GLuint s, std::string shaderType)
    {
        GLint isCompiled = 0;
        glGetShaderiv(s, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(s, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(s, maxLength, &maxLength, &infoLog[0]);
            glDeleteShader(s);
            std::cout << "Compiler error in " << shaderType << '\n';
            for (std::vector<GLchar>::const_iterator i = infoLog.begin(); i != infoLog.end(); ++i)
                std::cout << *i;
            return;
        }
        std::cout << shaderType << " compiled\n";
    }

    void RemoveShaders()
    {
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
    }

    void ReloadShaders()
    {
        RemoveShaders();
        AddVertexShader();
        AddFragmentShader();
        Use();
        std::cout << "Shaders reloaded\n\n";
    }
};

#endif