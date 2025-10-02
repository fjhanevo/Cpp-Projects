#include "shader.h"

#include <iostream>

Shader &Shader::use()
{
    glUseProgram(this->ID);
    return *this;
}

void Shader::compile(const char *vertex_source, const char *fragment_source)
{
    unsigned int s_vertex, s_fragment;

    // vertex shader
    s_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(s_vertex, 1, &vertex_source, NULL);
    glCompileShader(s_vertex);
    check_compile_errors(s_vertex, "VERTEX");

    // fragment shader
    s_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(s_fragment, 1, &fragment_source, NULL);
    glCompileShader(s_fragment);
    check_compile_errors(s_fragment, "FRAGMENT");

    this->ID = glCreateProgram();
    glAttachShader(this->ID, s_vertex);
    glAttachShader(this->ID, s_fragment);
    glLinkProgram(this->ID);
    check_compile_errors(this->ID, "PROGRAM");

    // delete when linking is done
    glDeleteShader(s_vertex);
    glDeleteShader(s_fragment);

}

void Shader::set_bool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::set_int(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_float(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_vec2(const std::string &name, glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::set_vec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::set_mat2(const std::string &name, glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_mat3(const std::string &name, glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_mat4(const std::string &name, glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::check_compile_errors(unsigned int shader, std::string type)
{
    int success;
    char info_log[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, info_log);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << '\n'
                << info_log << '\n';
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, info_log);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << '\n' 
                << info_log << '\n';
        }
    }
}


