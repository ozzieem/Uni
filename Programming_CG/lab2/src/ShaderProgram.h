#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "readfile.hpp"
#include <vector>

class ShaderProgram
{
  public:
    static const char *vertexFile;
    static const char *fragmentFile;

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

    void SetVertexPosition(GLfloat posChange, GLint idx)
    {
        GLint uniLoc = glGetUniformLocation(program, "pos_offset");
        PosOffset[idx] += posChange;
        glUniform2fv(uniLoc, 1, PosOffset);
    }

    void SetFragmentModifier(GLfloat scrV, GLfloat scrH)
    {
        GLint uniLoc = glGetUniformLocation(program, "modifier");
        GLint scrollDamper = 100;
        scrollOffset += scrV / scrollDamper;
        scrollOffset -= scrH / scrollDamper;
        glUniform1f(uniLoc, scrollOffset);
    }

    void AddVertexShader()
    {
        vertexShader = CreateShader(vertexFile, GL_VERTEX_SHADER);
        AddShader(vertexShader, "VertexShader");
        std::cout << "Vertexshader added" << '\n';
    }

    void AddFragmentShader()
    {
        fragmentShader = CreateShader(fragmentFile, GL_FRAGMENT_SHADER);
        AddShader(fragmentShader, "FragmentShader");
        std::cout << "Fragmentshader added" << '\n';
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
        std::cout << "Shaders removed\n";
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