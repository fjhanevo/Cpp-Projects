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

void Shader::set_int(const std::string &name, int value, bool use_shader)
{
    if (use_shader)
        this->use();
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::set_float(const std::string &name, float value, bool use_shader)
{
    if (use_shader)
        this->use();
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::set_vec2(const std::string &name, glm::vec2 &value, bool use_shader)
{
    if (use_shader)
        this->use();
    glUniform2f(glGetUniformLocation(this->ID, name.c_str()), value.x, value.y);
}

void Shader::set_vec2(const std::string &name, float x, float y, bool use_shader)
{
    if (use_shader)
        this->use();
    glUniform2f(glGetUniformLocation(this->ID, name.c_str()), x, y);
}
void Shader::set_vec3(const std::string &name, glm::vec3 &value, bool use_shader)
{
    if (use_shader)
        this->use();
    glUniform3f(glGetUniformLocation(this->ID, name.c_str()), value.x, value.y, value.z);
}
void Shader::set_vec3(const std::string &name, float x, float y,float z, bool use_shader)
{
    if (use_shader)
        this->use();
    glUniform3f(glGetUniformLocation(this->ID, name.c_str()), x, y, z);
}

void Shader::set_vec4(const std::string &name, glm::vec4 &value, bool use_shader)
{
    if (use_shader)
        this->use();
    glUniform4f(glGetUniformLocation(this->ID, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::set_vec4(const std::string &name, float x, float y,float z, float w, bool use_shader)
{
    if (use_shader)
        this->use();
    glUniform4f(glGetUniformLocation(this->ID, name.c_str()), x, y, z, w);
}


void Shader::set_mat2(const std::string &name, glm::mat2 &mat, bool use_shader)
{
    if (use_shader)
        this->use();
    glUniformMatrix2fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_mat3(const std::string &name, glm::mat3 &mat, bool use_shader)
{
    if (use_shader)
        this->use();
    glUniformMatrix3fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::set_mat4(const std::string &name, glm::mat4 &mat, bool use_shader)
{
    if (use_shader)
        this->use();
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


